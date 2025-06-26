#pragma once
#include "Entity.h"
#include "Graphics.h"

/**
 * @class UFO
 * @brief Represents a UFO entity that periodically appears in the game.
 *
 * The UFO moves across the screen, can be destroyed by the player, and awards points.
 * It manages its own spawn timer to appear at intervals.
 */
class UFO : public Entity{
public:
  /**
   * @brief Constructs a UFO with a reference to the graphics context.
   * @param graphics Pointer to the Graphics object used for rendering.
   */
  UFO(Graphics* graphics);

  /** Destructor */
  ~UFO();

  /**
   * @brief Updates the UFO state, including movement and spawn timer.
   * @param deltaTime Time elapsed since the last update (in seconds).
   */
  void update(float deltaTime);

  /**
   * @brief Renders the UFO on the screen.
   */
  void render() override;

  /**
   * @brief Gets the bounding box of the UFO for collision detection.
   * @return SDL_FRect representing the UFO's bounds.
   */
  SDL_FRect getBounds() const override;

  /**
   * @brief Checks whether the UFO has been destroyed.
   * @return True if destroyed, false otherwise.
   */
  bool isDestroyed() const override { return destroyed; }

  /**
   * @brief Marks the UFO as destroyed.
   */
  void destroy() override { destroyed = true; }

  /**
   * @brief Resets only the spawn timer, without changing active or destroyed states.
   */
  void resetTimerOnly();

  /**
   * @brief Gets the score value awarded when the UFO is destroyed.
   * @return Integer score value.
   */
  int getScoreValue() const { return scoreValue; }

  /**
   * @brief Checks if the UFO is currently active (visible and moving).
   * @return True if active, false otherwise.
   */
  bool isActive() const { return active; }

  /**
   * @brief Fully resets the UFO to its initial state.
  */
  void reset();

private:
  Graphics* graphics;               ///< Graphics context for rendering.
  SDL_FPoint velocity{0.0f, 0.0f};  ///< Current velocity of the UFO.

  float width = 50.0f;              ///< Width of the UFO sprite.
  float height = 25.0f;             ///< Height of the UFO sprite.

  bool destroyed = false;           ///< True if the UFO is destroyed.
  bool active = false;              ///< True if the UFO is active on screen.
  float spawnTimer = 0.0f;          ///< Timer counting down to next spawn.
  float spawnInterval = 15.0f;      ///< Time interval between spawns in seconds.

  int scoreValue = 100;             ///< Score awarded for destroying the UFO.

  /**
   * @brief Resets the spawn timer to a random value between minSeconds and maxSeconds.
   * @param minSeconds Minimum seconds for the timer.
   * @param maxSeconds Maximum seconds for the timer.
   */
  void resetSpawnTimer(float minSeconds, float maxSeconds);
};
