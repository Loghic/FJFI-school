/**
 * @file Graphics.cpp
 * @brief Implementation of the Graphics class for simplified SDL2 rendering operations.
 *
 * This file defines the member functions of the Graphics class, which provides a wrapper
 * around SDL2 rendering functionality. It includes utilities for clearing the screen,
 * drawing basic shapes (rectangles, lines), rendering textures (with optional transformations),
 * and caching loaded textures to improve performance.
 *
 * Dependencies:
 * - SDL2 (SDL_render.h, SDL_surface.h)
 * - Custom Color struct (defined elsewhere)
 */
#include "Graphics.h"
#include <SDL_render.h>
#include <SDL_surface.h>
#include <iostream>

/**
 * @brief Constructs a Graphics object that wraps SDL rendering operations.
 *
 * @param renderer A valid SDL_Renderer pointer used for all rendering tasks.
 */
Graphics::Graphics(SDL_Renderer* renderer)
  : renderer(renderer) {
}

/**
 * @brief Destructor. Cleans up any cached textures.
 */
Graphics::~Graphics() {
  // Clean up texture cache
  for (auto& [path, texture] : textureCache) {
      SDL_DestroyTexture(texture);
  }
  textureCache.clear();
}

/**
 * @brief Clears the screen with the specified color.
 *
 * @param color The color to use when clearing the screen.
 */
void Graphics::clear(const Color& color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(renderer);
}

/**
 * @brief Presents the rendered content to the screen.
 */
void Graphics::present() {
  SDL_RenderPresent(renderer);
}

/**
 * @brief Draws a rectangle to the screen.
 *
 * @param rect The rectangle bounds in floating-point coordinates.
 * @param color The color to draw the rectangle with.
 * @param filled If true, the rectangle is filled; otherwise, it is only outlined.
 */
void Graphics::drawRect(const SDL_FRect& rect, const Color& color, bool filled) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  SDL_Rect intRect = {
      static_cast<int>(rect.x + 0.5f),
      static_cast<int>(rect.y + 0.5f),
      static_cast<int>(rect.w + 0.5f),
      static_cast<int>(rect.h + 0.5f)
  };

  if (filled) {
    SDL_RenderFillRect(renderer, &intRect);
  } else {
    SDL_RenderDrawRect(renderer, &intRect);
  }
}

/**
 * @brief Draws a line between two points.
 *
 * @param x1 Starting X coordinate.
 * @param y1 Starting Y coordinate.
 * @param x2 Ending X coordinate.
 * @param y2 Ending Y coordinate.
 * @param color Color of the line.
 */
void Graphics::drawLine(float x1, float y1, float x2, float y2, const Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

/**
 * @brief Loads a BMP texture from disk or returns a cached version.
 *
 * @param path Path to the BMP file.
 * @return SDL_Texture* Pointer to the loaded texture, or nullptr on failure.
 */
SDL_Texture* Graphics::loadTexture(const std::string& path) {
  // Check if texture is already loaded
  auto it = textureCache.find(path);
  if (it != textureCache.end()) {
    return it->second;
  }

  // Load the texture
  SDL_Surface* surface = SDL_LoadBMP(path.c_str());
  if (!surface) {
    std::cerr << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  // Cache and return the texture
  textureCache[path] = texture;
  return texture;
}

/**
 * @brief Draws a texture to the screen with optional transformations.
 *
 * @param texture The texture to draw.
 * @param destRect Destination rectangle in float coordinates.
 * @param srcRect Optional source rectangle. Pass nullptr to draw the entire texture.
 * @param angle Rotation angle in degrees.
 * @param center Optional rotation center. If nullptr, rotation is around the center of destRect.
 * @param flip Optional flip settings (horizontal/vertical).
 */
void Graphics::drawTexture(SDL_Texture* texture, const SDL_FRect& destRect,
                          const SDL_FRect* srcRect, float angle,
                          const SDL_FPoint* center, SDL_RendererFlip flip) {
  if (!texture) return;

  SDL_RenderCopyEx(
    renderer,
    texture,
    reinterpret_cast<const SDL_Rect*>(srcRect), // optional src rect
    reinterpret_cast<const SDL_Rect*>(&destRect), // destination
    angle,
    reinterpret_cast<const SDL_Point*>(center), // optional center
    flip
  );
}
