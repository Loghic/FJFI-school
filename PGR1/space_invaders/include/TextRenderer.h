#pragma once
#include <SDL2/SDL.h>
#include <SDL_rect.h>
#include <string>
#include <unordered_map>
#include "Graphics.h"

// Include SDL-ttf if available
#ifndef NO_SDL_TTF
#include <SDL_ttf.h>
#endif

/**
 * @class TextRenderer
 * @brief Handles rendering of text using SDL_ttf or a fallback method.
 *
 * Provides functionality to load fonts, render text with alignment,
 * and query text dimensions. Supports caching of rendered text textures
 * for performance. Uses SDL_ttf when available, otherwise uses a basic
 * fallback renderer.
 */
class TextRenderer {
public:
  /**
   * @brief Constructs a TextRenderer.
   * @param graphics Pointer to Graphics object for drawing utilities.
   * @param renderer SDL_Renderer pointer used for rendering textures.
   */
  TextRenderer(Graphics* graphics, SDL_Renderer* renderer);

  /** Destructor cleans up font and cached textures if applicable. */
  ~TextRenderer();

  /**
   * @brief Loads a font from the specified file path at a given size.
   * @param path Path to the font file (e.g., TTF file).
   * @param fontSize Size (in points) of the font to load.
   * @return True if the font loaded successfully; false otherwise.
   */
  bool loadFont(const std::string& path, int fontSize);

  /**
   * @brief Draws text at a given position with the specified color and alignment.
   * @param text The string to render.
   * @param x The x-coordinate for the text position.
   * @param y The y-coordinate for the text position.
   * @param color The color of the rendered text.
   * @param centered If true, text is centered horizontally around (x, y). Otherwise, text starts at (x, y).
   */
  void drawText(const std::string& text, float x, float y, const Color& color,
                bool centered = true);

  /**
   * @brief Calculates and returns the width and height of a given text string.
   * @param text The string to measure.
   * @return SDL_FPoint containing the width (x) and height (y) of the rendered text.
   */
  SDL_FPoint getTextSize(const std::string& text);

private:
  Graphics* graphics;       ///< Pointer to Graphics utility for rendering.
  SDL_Renderer* renderer;   ///< SDL renderer for drawing.

#ifndef NO_SDL_TTF
  TTF_Font* font = nullptr; ///< Loaded TTF font pointer.
  /// Cache of rendered text strings to SDL_Texture pointers for performance.
  std::unordered_map<std::string, SDL_Texture*> textCache;

#endif

  /**
   * @brief Fallback text drawing when SDL_ttf is unavailable.
   * Renders text as simple rectangles or placeholders.
   * @param text The string to render.
   * @param x The x-coordinate for the text position.
   * @param y The y-coordinate for the text position.
   * @param color The color of the text.
   * @param centered Whether to center the text horizontally.
   */
  void drawTextFallback(const std::string& text, float x, float y,
                        const Color& color, bool centered = true);

  // Constants for fallback rendering character dimensions and spacing.
  const float charWidth = 12.0f;
  const float charHeight = 20.0f;
  const float charSpacing = 2.0f;

  /**
   * @brief Draws a single character in fallback mode.
   * @param c The character to draw.
   * @param x The x-coordinate of the character's position.
   * @param y The y-coordinate of the character's position.
   * @param color The color to draw the character.
   */
  void drawCharFallback(char c, float x, float y, const Color& color);
};

