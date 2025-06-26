#pragma once
#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <string>
#include <unordered_map>

/**
 * @class Color
 * @brief Represents an RGBA color.
 *
 * Holds red, green, blue, and alpha components for color management.
 */
class Color {
public:
  Uint8 r,g,b,a;

  /**
   * @brief Constructs a Color with given RGBA values.
   * @param r Red component (0-255), default 255 (full red).
   * @param g Green component (0-255), default 255 (full green).
   * @param b Blue component (0-255), default 255 (full blue).
   * @param a Alpha (opacity) component (0-255), default 255 (fully opaque).
   */
  Color(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255)
      : r(r), g(g), b(b), a(a) {}
};

/**
 * @class Graphics
 * @brief Wrapper for SDL rendering functions and texture management.
 *
 * Manages an SDL_Renderer pointer and provides utilities for drawing primitives,
 * loading and caching textures, and rendering textures with transformations.
 */
class Graphics {
public:
  /**
   * @brief Constructs Graphics object tied to a given SDL_Renderer.
   * @param renderer Pointer to SDL_Renderer used for all rendering operations.
   */
  Graphics(SDL_Renderer* renderer);

  /** Destructor cleans up cached textures. */
  ~Graphics();

  /**
   * @brief Clears the rendering target with the specified color.
   * @param color Color to clear the screen with (default is opaque black).
   */
  void clear(const Color& color = Color(0,0,0, 255));

  /** Presents the rendered content to the screen. */
  void present();

  /**
   * @brief Draws a rectangle.
   * @param rect Rectangle position and size.
   * @param color Color of the rectangle.
   * @param filled If true, fills the rectangle; otherwise draws only the outline.
   */
  void drawRect(const SDL_FRect& rect, const Color& color, bool filled = true);

  /**
   * @brief Draws a line between two points.
   * @param x1 X-coordinate of the start point.
   * @param y1 Y-coordinate of the start point.
   * @param x2 X-coordinate of the end point.
   * @param y2 Y-coordinate of the end point.
   * @param color Color of the line.
   */
  void drawLine(float x1, float y1, float y2, float x2, const Color& color);

  /**
   * @brief Loads a texture from a file path, caching it for reuse.
   * @param path File path of the texture image.
   * @return Pointer to SDL_Texture, or nullptr if loading failed.
   */
  SDL_Texture* loadTexture(const std::string& path);

  /**
   * @brief Draws a texture to the rendering target.
   * @param texture Pointer to the SDL_Texture to draw.
   * @param destRect Destination rectangle specifying position and size.
   * @param srcRect Source rectangle to draw from the texture (nullptr to draw whole texture).
   * @param angle Rotation angle in degrees (default 0).
   * @param center Point around which to rotate (nullptr rotates around destRect center).
   * @param flip Flip mode (horizontal/vertical), default none.
   */
  void drawTexture(SDL_Texture* texture, const SDL_FRect& destRect,
                   const SDL_FRect* srcRect = nullptr, float angle = 0.0f,
                   const SDL_FPoint* center = nullptr,
                   SDL_RendererFlip flip  = SDL_FLIP_NONE);

  /** @return Pointer to the SDL_Renderer used internally. */
  SDL_Renderer* getRenderer() const {return renderer; }

private:
  SDL_Renderer* renderer;  ///< The SDL_Renderer used for rendering.

   /// Cache mapping file paths to loaded SDL_Textures to avoid reloading.
  std::unordered_map<std::string, SDL_Texture*> textureCache;

};

