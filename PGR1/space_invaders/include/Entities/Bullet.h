#pragma once
#include "Entity.h"
#include "Graphics.h"

/**
 * @class Bullet
 * @brief Represents a bullet entity in the game.
 *
 * The Bullet class manages the bullet's position, movement, rendering, and state.
 * It inherits from Entity and overrides necessary methods for update and rendering.
 */
class Bullet : public Entity {
public:
  /**
   * @brief Constructs a Bullet with a reference to the Graphics context.
   * @param graphics Pointer to the Graphics object used for rendering.
   */
  Bullet(Graphics* graphics);
  /** Destructor */
  ~Bullet();

  /**
   * @brief Updates the bullet's position based on its velocity and elapsed time.
   * @param deltaTime Time elapsed since last update (in seconds).
   */
  void update(float deltaTime);

  /**
   * @brief Renders the bullet on the screen.
   */
  void render() override;

  /**
   * @brief Sets the velocity of the bullet.
   * @param x Velocity in the X direction.
   * @param y Velocity in the Y direction.
   */
  void setVelocity(float x, float y);

  /**
   * @brief Checks if the bullet is destroyed.
   * @return True if destroyed, false otherwise.
   */
  SDL_FRect getBounds() const override;

  /**
   * @brief Checks if the bullet is destroyed.
   * @return True if destroyed, false otherwise.
   */
  bool isDestroyed() const override {return destroyed;}

  /** Marks the bullet as destroyed. */
  void destroy() override {destroyed = true;}

  /**
   * @brief Checks if the bullet is out of the screen bounds.
   * @return True if out of bounds, false otherwise.
   */
  bool isOutOfBounds() const;

private:
  Graphics* graphics;               ///< Graphics context for rendering.
  SDL_FPoint velocity{0.0f, 0.0f};  ///< Current velocity of the bullet.
  float width = 5.0f;               ///< Width of the bullet.
  float height = 15.0f;             ///< Height of the bullet.
  bool destroyed = false;           ///< Whether the bullet is destroyed.
};

