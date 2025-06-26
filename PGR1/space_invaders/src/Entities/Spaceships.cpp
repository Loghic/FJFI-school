/**
 * @file Spaceship.cpp
 * @brief Implements common functionality for all spaceship types, including bounding box and bullet management.
 *
 * This file provides shared utility methods used by player and enemy classes, such as calculating bounding rectangles
 * and updating/destroying bullets.
 */

#include "Entities/Spaceship.h"
#include "Entities/Bullet.h"
#include <algorithm>

/**
 * @brief Returns the bounding rectangle of the spaceship.
 *
 * This is used for collision detection and rendering.
 *
 * @return SDL_FRect The rectangle representing the ship's bounds.
 */
SDL_FRect Spaceship::getBounds() const {
  return SDL_FRect{
    position.x - width * 0.5f,
    position.y - height * 0.5f,
    width,
    height
  };
}

/**
 * @brief Updates all bullets fired by the spaceship and removes destroyed or out-of-bounds bullets.
 *
 * This ensures bullets continue moving and cleans up memory when they’re no longer needed.
 *
 * @param deltaTime Time since last frame in seconds.
 */
void Spaceship::updateBullets(float deltaTime) {
  for (auto& bullet : bullets) {
    bullet->update(deltaTime);
  }

  bullets.erase(
    std::remove_if(bullets.begin(), bullets.end(),
      [](const std::unique_ptr<Bullet>& bullet) {
        return bullet->isDestroyed() || bullet->isOutOfBounds();
      }),
    bullets.end()
  );
}

