#pragma once
#include "Entity.h"
#include <vector>
#include <memory>

class Graphics;
class Bullet;

/**
 * @class Spaceship
 * @brief Abstract base class representing a spaceship entity.
 *
 * Provides common properties and behavior for player and enemy spaceships,
 * including position, size, velocity, rendering interface, and bullet management.
 */
class Spaceship : public Entity {
public:
  /** Virtual destructor to ensure proper cleanup in derived classes */
  virtual ~Spaceship() = default;

  /**
   * @brief Renders the spaceship.
   * Must be implemented by derived classes.
   */
  virtual void render() override = 0;

  /**
   * @brief Gets the bounding rectangle of the spaceship for collision or rendering.
   * @return SDL_FRect representing the spaceship bounds.
   */
  SDL_FRect getBounds() const override;

  /**
   * @brief Accesses the bullets currently fired by this spaceship.
   * @return Const reference to a vector of unique pointers to Bullet objects.
   */
  const std::vector<std::unique_ptr<Bullet>>& GetBullets() const
    { return bullets; }

  protected:
  /**
   * @brief Protected constructor for derived spaceship classes.
   * @param graphics Pointer to the Graphics context for rendering.
   * @param width Width of the spaceship.
   * @param height Height of the spaceship.
   */
  Spaceship(Graphics* graphics, float width, float height)
    : graphics(graphics), width(width), height(height) {}

  /**
   * @brief Updates all bullets fired by the spaceship.
   * Moves bullets and removes those that are destroyed or out of bounds.
   * @param deltaTime Time elapsed since last update (in seconds).
   */
  void updateBullets(float deltaTime);

  Graphics* graphics;               ///< Pointer to graphics context used for rendering.
  SDL_FPoint velocity {0.0f, 0.0f}; ///< Current velocity of the spaceship.

  float width;                      ///< Width of the spaceship sprite or collision box.
  float height;                     ///< Height of the spaceship sprite or collision box.
  ///
  std::vector<std::unique_ptr<Bullet>> bullets; ///< Bullets fired by the spaceship.
};

