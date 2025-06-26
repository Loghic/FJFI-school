/**
 * @file UFO.cpp
 * @brief Implements the behavior of the flying UFO enemy in the game.
 *
 * This file manages the UFO's spawning, movement across the screen, and rendering.
 * The UFO appears at random intervals and moves horizontally across the screen.
 */

#include "Entities/UFO.h"
#include <random>

/**
 * @brief Constructs a UFO object and initializes spawn timing.
 *
 * The UFO starts inactive and with a randomized spawn timer.
 *
 * @param graphics Pointer to the Graphics system used for rendering.
 */
UFO::UFO(Graphics* graphics) : graphics(graphics) {
  // Initialize with random spawn timer
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(5.0f, spawnInterval);
  spawnTimer = dist(gen);

  // UFO starts inactive
  active = false;
  destroyed = false;
}

/**
 * @brief Destructor for the UFO class.
 */
UFO::~UFO() {
}

/**
 * @brief Resets the UFO spawn timer with a new randomized interval.
 *
 * @param minSeconds Minimum time before UFO can respawn.
 * @param maxSeconds Maximum time before UFO can respawn.
 */
void UFO::resetSpawnTimer(float minSeconds, float maxSeconds) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(minSeconds, maxSeconds);
  spawnTimer = dist(gen);
}

/**
 * @brief Resets the UFO state to inactive and resets its spawn timer.
 */
void UFO::resetTimerOnly() {
  active = false;
  destroyed = false;

  resetSpawnTimer(10.0f, spawnInterval);
}

/**
 * @brief Updates the UFO's state and position.
 *
 * If inactive, it checks whether it's time to spawn.
 * If active, it moves across the screen and resets if it goes off-screen.
 *
 * @param deltaTime Time since the last update (in seconds).
 */
void UFO::update(float deltaTime) {
  if (destroyed) return;

  if (!active) {
    spawnTimer -= deltaTime;
    if (spawnTimer <= 0.0f) {
      active = true;
      position.x = -width;
      position.y = 50.0f;
      velocity.x = 150.0f;
      resetSpawnTimer(10.0f, spawnInterval);
    }
  } else {
    position.x += velocity.x * deltaTime;

    if (position.x > 800 + width) {
      active = false;
      destroyed = false;
      resetSpawnTimer(10.0f, spawnInterval);
    }
  }
}

/**
 * @brief Renders the UFO on screen if it is active and not destroyed.
 *
 * The UFO is rendered as a rectangle with a cockpit for visual flair.
 */
void UFO::render() {
  if (!active || destroyed) return;

  // Draw UFO as an ellipse (approximated with a rectangle)
  Color ufoColor(255, 0, 255);  // Purple
  SDL_FRect ufoRect = {
    position.x - width * 0.5f,
    position.y - height * 0.5f,
    width,
    height
  };

  graphics->drawRect(ufoRect, ufoColor, true);

  // Draw a "cockpit" in the middle
  Color cockpitColor(150, 150, 255);  // Light blue
  SDL_FRect cockpitRect = {
    position.x - width * 0.2f,
    position.y - height * 0.25f,
    width * 0.4f,
    height * 0.5f
  };

  graphics->drawRect(cockpitRect, cockpitColor, true);
}

/**
 * @brief Returns the bounding rectangle of the UFO for collision detection.
 *
 * @return SDL_FRect The bounding box of the UFO.
 */
SDL_FRect UFO::getBounds() const {
  return SDL_FRect{
    position.x - width * 0.5f,
    position.y - height * 0.5f,
    width,
    height
  };
}

/**
 * @brief Fully resets the UFO to its initial state.
 */
void UFO::reset() {
  active = false;
  destroyed = false;
  position = { -width, 50.0f };
  velocity = { 150.0f, 0.0f };
  resetSpawnTimer(5.0f, spawnInterval);
}
