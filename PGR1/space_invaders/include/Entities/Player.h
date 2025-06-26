#pragma once
#include "Spaceship.h"

/**
 * @class Player
 * @brief Represents the player-controlled spaceship in the game.
 *
 * Extends Spaceship with player-specific controls, lives, shooting,
 * and input event handling.
 */
class Player : public Spaceship {
public:
  /**
   * @brief Constructs a Player with the provided Graphics context.
   * @param graphics Pointer to the Graphics object used for rendering.
   */
  Player(Graphics* graphics);

  /** Destructor */
  ~Player();

  /**
   * @brief Handles input events to update player state.
   * @param event SDL_Event to process (e.g., keyboard, mouse).
   */
  void handleEvent(const SDL_Event& event);

  /**
   * @brief Updates the player state, including movement and shooting cooldown.
   * @param deltaTime Time elapsed since last update (in seconds).
   */
  void update(float deltaTime);

  /**
   * @brief Renders the player spaceship on screen.
   */
  void render();

  /**
   * @brief Resets the player state (e.g., lives and position) for a new game or respawn.
   */
  void reset();

  /**
   * @brief Checks whether the player is destroyed (no remaining lives).
   * @return True if lives are zero or less, otherwise false.
   */
  bool isDestroyed() const { return lives <= 0; }

  /**
   * @brief Marks the player as destroyed by setting lives to zero.
   */
  void destroy() { lives = 0; }

  /**
   * @brief Decreases the player's lives by one when taking damage.
   */
  void takeDamage();

  /**
   * @brief Gets the current number of lives the player has.
   * @return The number of remaining lives.
   */
  int getLives() const { return lives; }

private:
  float moveSpeed = 300.0f;    ///< Movement speed in pixels per second.
  float shootCooldown = 0.0f;  ///< Time remaining until player can shoot again.
  int lives = 3;               ///< Number of lives the player has.

  // Key states
  bool moveLeft = false;
  bool moveRight = false;
  bool isShooting = false;

  /**
   * @brief Fires a projectile if shoot cooldown has elapsed.
   */
  void shoot();
};

