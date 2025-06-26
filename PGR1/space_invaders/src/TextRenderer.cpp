/**
 * @file TextRenderer.cpp
 * @brief Implementation of the TextRenderer class for rendering text using SDL_ttf or fallback methods.
 *
 * This class provides functionality to render text on the screen using SDL_ttf when available.
 * It manages font loading, text caching to textures for efficient rendering, and also
 * includes a fallback rendering method using basic shapes if SDL_ttf is not available.
 *
 * Dependencies:
 * - SDL2 (SDL_surface.h)
 * - SDL_ttf (conditionally compiled)
 * - Graphics class for basic drawing
 */
#include "TextRenderer.h"
#include <SDL_surface.h>
#include <iostream>

/**
 * @brief Constructs a TextRenderer with references to a Graphics instance and SDL_Renderer.
 *        Initializes SDL_ttf if available.
 *
 * @param graphics Pointer to Graphics instance for fallback drawing.
 * @param renderer Pointer to SDL_Renderer used for rendering textures.
 */
TextRenderer::TextRenderer(Graphics* graphics, SDL_Renderer* renderer)
  : graphics(graphics), renderer(renderer) {
#ifndef NO_SDL_TTF
  // Initialize SDL_ttf
  if (TTF_Init() != 0) {
    std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
  }
#endif
}

/**
 * @brief Destructor frees cached text textures, closes loaded font, and quits SDL_ttf.
 */
TextRenderer::~TextRenderer() {
#ifndef NO_SDL_TTF
  // Free cached textures
  for (auto& [key, texture] : textCache) {
      SDL_DestroyTexture(texture);
  }
  textCache.clear();

  // Close font
  if (font) {
      TTF_CloseFont(font);
      font = nullptr;
  }

  // Quit SDL_ttf
  TTF_Quit();
#endif
}

/**
 * @brief Loads a TrueType font from a given file path with specified size.
 *
 * @param path Path to the font file.
 * @param fontSize Font size to load.
 * @return true if font is successfully loaded, false otherwise.
 */
bool TextRenderer::loadFont(const std::string& path, int fontSize) {
#ifndef NO_SDL_TTF
  // Close previous font if exists
  if (font) {
      TTF_CloseFont(font);
      font = nullptr;
  }

  // Load new font
  font = TTF_OpenFont(path.c_str(), fontSize);
  if (!font) {
      std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
      return false;
  }

  return true;
#else
    // SDL_ttf not available
    return false;
#endif
}

/**
 * @brief Renders text at given position with specified color, optionally centered.
 *
 * If SDL_ttf is available and font is loaded, renders text to a cached texture for efficiency.
 * Otherwise, falls back to simple shape-based rendering.
 *
 * @param text The string to render.
 * @param x The x-coordinate to draw the text.
 * @param y The y-coordinate to draw the text.
 * @param color Color to render the text with.
 * @param centered Whether to center the text around (x, y).
 */
void TextRenderer::drawText(const std::string& text, float x, float y, const Color& color, bool centered) {
#ifndef NO_SDL_TTF
  if (font) {
    // Check if text is already cached
    std::string cacheKey = text + "_" + std::to_string(color.r) + "_" +
                                        std::to_string(color.g) + "_" +
                                        std::to_string(color.b) + "_" +
                                        std::to_string(color.a);

    SDL_Texture* texture = nullptr;

    // Try to find in cache
    auto it = textCache.find(cacheKey);
    if (it != textCache.end()) {
      texture = it->second;
    } else {
      // Create SDL color
      SDL_Color sdlColor = { color.r, color.g, color.b, color.a };

      // Render text to surface
      SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
      if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        drawTextFallback(text, x, y, color, centered);
        return;
      }

      // Create texture from surface
      texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface);

      if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        drawTextFallback(text, x, y, color, centered);
        return;
      }

      // Cache the texture
      textCache[cacheKey] = texture;
    }

    // Get texture dimensions
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    // Calculate position
    float textX = x;
    float textY = y;

    if (centered) {
      textX -= width / 2.0f;
      textY -= height / 2.0f;
    }

    // Draw texture
    SDL_FRect destRect = { textX, textY, (float)width, (float)height };
    SDL_RenderCopyF(renderer, texture, nullptr, &destRect);

    return;
  }
#endif

  // Fallback to primitive rendering
  drawTextFallback(text, x, y, color, centered);
}

/**
 * @brief Returns the width and height of a rendered text string.
 *
 * Uses SDL_ttf to measure text size if font is loaded, otherwise returns an estimated size
 * based on character width and spacing.
 *
 * @param text The string to measure.
 * @return SDL_FPoint containing width (x) and height (y).
 */
SDL_FPoint TextRenderer::getTextSize(const std::string& text) {
#ifndef NO_SDL_TTF
  if (font) {
    int width, height;
    TTF_SizeText(font, text.c_str(), &width, &height);
    return { (float)width, (float)height };
  }
#endif

  // Fallback size calculation
  return { text.length() * (charWidth + charSpacing), charHeight };
}

/**
 * @brief Fallback method to render text using basic shapes when SDL_ttf is unavailable.
 *
 * Draws each character using simple rectangles and lines with the Graphics instance.
 *
 * @param text The string to render.
 * @param x The x-coordinate to start drawing.
 * @param y The y-coordinate to start drawing.
 * @param color Color of the text.
 * @param centered Whether to center the text horizontally at (x, y).
 */
void TextRenderer::drawTextFallback(const std::string& text, float x, float y, const Color& color, bool centered) {
  float totalWidth = text.length() * (charWidth + charSpacing);

  // Calculate start position
  float startX = x;
  if (centered) {
    startX -= totalWidth / 2;
  }

  // Draw each character
  for (size_t i = 0; i < text.length(); i++) {
    float charX = startX + i * (charWidth + charSpacing);
    drawCharFallback(text[i], charX, centered ? y - charHeight/2 : y, color);
  }
}

/**
 * @brief Draws a single character using simple shapes as a fallback.
 *
 * Handles uppercase letters, lowercase letters, digits, spaces, and other characters
 * with simple geometric approximations.
 *
 * @param c The character to draw.
 * @param x The x-coordinate to draw the character.
 * @param y The y-coordinate to draw the character.
 * @param color The color to draw the character with.
 */
void TextRenderer::drawCharFallback(char c, float x, float y, const Color& color) {
  // Simplified fallback character rendering using basic shapes
  if (c >= 'A' && c <= 'Z') {
    // Draw uppercase letter with a simple rectangle
    SDL_FRect rect = { x, y, charWidth, charHeight };
    graphics->drawRect(rect, color, false);

    // Draw a line inside to make it look a bit different
    graphics->drawLine(x, y + charHeight/2, x + charWidth, y + charHeight/2, color);
  }
  else if (c >= 'a' && c <= 'z') {
    // Draw lowercase letter with a smaller rectangle
    SDL_FRect rect = { x, y + charHeight*0.25f, charWidth, charHeight*0.75f };
    graphics->drawRect(rect, color, false);
  }
  else if (c >= '0' && c <= '9') {
    // Draw number with a simple box
    SDL_FRect rect = { x, y, charWidth, charHeight };
    graphics->drawRect(rect, color, false);
  }
  else if (c == ' ') {
    // Space character - do nothing
  }
  else {
    // Draw other characters as a small box
    SDL_FRect rect = { x + charWidth/4, y + charHeight/4, charWidth/2, charHeight/2 };
    graphics->drawRect(rect, color, true);
  }
}
