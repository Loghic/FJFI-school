#pragma once
#include "Spaceship.h"

/**
 * @class Enemy
 * @brief Represents an enemy spaceship in the game.
 *
 * Inherits from Spaceship and adds behavior for moving, shooting, and interacting
 * with the player. Handles update and rendering logic specific to enemy ships.
 */
class Enemy : public Spaceship{
public:
  /**
   * @brief Constructs an Enemy with a reference to the Graphics context.
   * @param graphics Pointer to the Graphics object used for rendering.
   */
  Enemy(Graphics* graphics);

  /** Destructor */
  ~Enemy();

  /**
   * @brief Updates the enemy state each frame.
   *
   * Moves the enemy, manages shooting cooldowns, and targets the player.
   *
   * @param deltaTime Time elapsed since last update (in seconds).
   * @param playerPosition Current position of the player for aiming.
   */
  void update(float deltaTime, const SDL_FPoint& playerPosition);

  /**
   * @brief Renders the enemy spaceship on the screen.
   */
  void render();


  /**
   * @brief Checks if the enemy is destroyed.
   * @return True if destroyed, false otherwise.
   */
  bool isDestroyed() const { return destroyed; }

  /** Marks the enemy as destroyed. */
  void destroy() {destroyed = true; }

private:
  float moveSpeed = 50.0f;          ///< Movement speed of the enemy.
  float dropAmount = 15.0f;         ///< Amount to drop vertically when hiting the wall.
  float shootCooldown = 0.0f;       ///< Timer to control shooting intervals.
  float shootProbability = 0.0005f; ///< Probability of shooting each frame.

  bool destroyed = false;           ///< Whether the enemy is destroyed.

  /**
   * @brief Handles shooting behavior targeting the player.
   * @param playerPosition Position of the player to aim at.
   */
  void shoot(const SDL_FPoint& playerPosition);
};

