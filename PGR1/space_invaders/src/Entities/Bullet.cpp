/**
 * @file Bullet.cpp
 * @brief Implements the Bullet class used to represent player or enemy projectiles.
 *
 * Bullets are small, fast-moving objects affected by velocity and subject to screen bounds.
 * Each bullet handles its own position update, rendering, and out-of-bounds detection.
 */
#include "Entities/Bullet.h"

/**
 * @brief Constructs a Bullet object.
 *
 * @param graphics Pointer to the Graphics object used for rendering.
 */
Bullet::Bullet(Graphics* graphics) : graphics(graphics) {
}

/**
 * @brief Destructor for the Bullet.
 */
Bullet::~Bullet() {
}

/**
 * @brief Updates the bullet's position based on its velocity.
 *
 * If the bullet is destroyed, no update is performed.
 *
 * @param deltaTime Time elapsed since the last frame.
 */
void Bullet::update(float deltaTime) {
  if (destroyed) return;

  // Update position based on velocity
  position.x += velocity.x * deltaTime;
  position.y += velocity.y * deltaTime;
}

/**
 * @brief Renders the bullet as a small yellow rectangle.
 *
 * Rendering is skipped if the bullet is marked as destroyed.
 */
void Bullet::render() {
  if (destroyed) return;

  // Draw bullet as a small rectangle
  Color bulletColor(255, 255, 0);  // Yellow
  SDL_FRect bulletRect = {
    position.x - width * 0.5f,
    position.y - height * 0.5f,
    width,
    height
  };

  graphics->drawRect(bulletRect, bulletColor, true);
}

/**
 * @brief Sets the velocity vector of the bullet.
 *
 * @param x Velocity in the X direction.
 * @param y Velocity in the Y direction.
 */
void Bullet::setVelocity(float x, float y) {
  velocity.x = x;
  velocity.y = y;
}

/**
 * @brief Returns the bounding rectangle of the bullet for collision detection.
 *
 * @return SDL_FRect representing the bullet's bounding box.
 */
SDL_FRect Bullet::getBounds() const {
  return SDL_FRect{
    position.x - width * 0.5f,
    position.y - height * 0.5f,
    width,
    height
  };
}

/**
 * @brief Checks whether the bullet has moved outside the screen boundaries.
 *
 * @return true if the bullet is out of bounds, false otherwise.
 */
bool Bullet::isOutOfBounds() const {
  // Check if bullet is outside the screen
  return position.y < -height || position.y > 600 + height ||
         position.x < -width || position.x > 800 + width;
}

