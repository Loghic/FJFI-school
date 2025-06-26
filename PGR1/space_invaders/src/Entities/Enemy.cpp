/**
 * @file Enemy.cpp
 * @brief Implementation of the Enemy class representing enemy ships in the game.
 *
 * Enemy objects move horizontally, reverse direction when hitting screen edges,
 * descend toward the player, and occasionally shoot bullets aimed at the player's position.
 */
#include "Entities/Enemy.h"
#include "Entities/Bullet.h"
#include <random>
#include <memory>

/**
 * @brief Constructs an Enemy object with default size and initial horizontal velocity.
 *
 * @param graphics Pointer to the Graphics instance for rendering.
 */
Enemy::Enemy(Graphics* graphics)
  : Spaceship(graphics, 30.0f, 30.0f) {
  velocity = {50.0f, 0.0f};
}

/**
 * @brief Destructor for the Enemy.
 *
 * Clears all owned bullets.
 */
Enemy::~Enemy() {
  bullets.clear();
}

/**
 * @brief Updates the enemy's position, handles shooting logic, and updates bullets.
 *
 * - Moves enemy horizontally.
 * - Reverses direction and drops down when reaching screen edges.
 * - Randomly decides when to shoot at the player's position.
 *
 * @param deltaTime Time since last update in seconds.
 * @param playerPosition The position of the player (used to aim bullets).
 */
void Enemy::update(float deltaTime, const SDL_FPoint& playerPosition) {
  if (destroyed) return;

  position.x += velocity.x * deltaTime;

  // Change direction at screen edges and move downward
  if (position.x <= width * 0.5f || position.x >= 800 - width * 0.5f) {
    // Reverse direction and move down
    velocity.x = -velocity.x;
    position.y += dropAmount;
  }

  // Countdown for next possible shot
  if (shootCooldown > 0.0f) {
    shootCooldown -= deltaTime;
  }

  // Random shooting - greatly reduced probability
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  if (shootCooldown <= 0.0f && dist(gen) < shootProbability) {
    shoot(playerPosition);
  }

  // Update bullets
  updateBullets(deltaTime);
}

/**
 * @brief Renders the enemy as a red rectangle with two white "eyes".
 *
 * Also renders all bullets currently active for this enemy.
 */
void Enemy::render() {
  if (destroyed) return;

  // Draw enemy as a rectangle
  Color enemyColor(255, 0, 0);  // Red
  SDL_FRect enemyRect = {
    position.x - width * 0.5f,
    position.y - height * 0.5f,
    width,
    height
  };

  graphics->drawRect(enemyRect, enemyColor, true);

  // Add some detail to make it look like an alien
  float eyeSize = width * 0.2f;
  Color eyeColor(255, 255, 255);  // White

  SDL_FRect leftEye = {
    position.x - width * 0.25f - eyeSize * 0.5f,
    position.y - height * 0.25f - eyeSize * 0.5f,
    eyeSize,
    eyeSize
  };

  SDL_FRect rightEye = {
    position.x + width * 0.25f - eyeSize * 0.5f,
    position.y - height * 0.25f - eyeSize * 0.5f,
    eyeSize,
    eyeSize
  };

  graphics->drawRect(leftEye, eyeColor, true);
  graphics->drawRect(rightEye, eyeColor, true);

  // Render bullets
  for (auto& bullet : bullets) {
    bullet->render();
  }
}

/**
 * @brief Fires a bullet toward the player's current position.
 *
 * Bullet is initialized at the bottom of the enemy and aimed by
 * normalizing the direction vector between the enemy and the player.
 *
 * @param playerPosition The current position of the player.
 */
void Enemy::shoot(const SDL_FPoint& playerPosition) {
  auto bullet = std::make_unique<Bullet>(graphics);
  bullet->setPosition(position.x, position.y + height * 0.5f);

  // Direction vector from enemy to player
  float dx = playerPosition.x - position.x;
  float dy = playerPosition.y - position.y;
  float length = std::sqrt(dx * dx + dy * dy);

  // Normalize and multiply by speed
  float speed = 300.0f;
  bullet->setVelocity((dx / length) * speed, (dy / length) * speed);

  bullets.push_back(std::move(bullet));

  shootCooldown = 5.0f;
}

