/**
 * @file Player.cpp
 * @brief Implementation of the Player class, which represents the controllable spaceship.
 *
 * The Player handles input events, movement, shooting, rendering, and managing lives.
 * Bullets are managed within the Player instance and are limited to one on screen at a time.
 */

#include "Entities/Player.h"
#include "Entities/Bullet.h"
#include <SDL_events.h>
#include <algorithm>
#include <iostream>
#include <memory>

/**
 * @brief Constructs the Player with a specified size and graphics context.
 *
 * @param graphics Pointer to the Graphics instance for rendering.
 */
Player::Player(Graphics* graphics)
  : Spaceship(graphics, 40.0f, 30.0f) {
}

/**
 * @brief Destructor for Player.
 *
 * Clears all active bullets.
 */
Player::~Player() {
  bullets.clear();
}

/**
 * @brief Handles SDL keyboard input events to control movement and shooting.
 *
 * Tracks key presses and releases for left/right movement and shooting.
 * Outputs debug logs to console for input events.
 *
 * @param event SDL_Event received from the event loop.
 */
void Player::handleEvent(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_LEFT:
      case SDL_SCANCODE_A:
        moveLeft = true;
        break;
      case SDL_SCANCODE_RIGHT:
      case SDL_SCANCODE_D:
        moveRight = true;
        break;
      case SDL_SCANCODE_SPACE:
        isShooting = true;
        break;
      default:
        // Unhandled keys are ignored
        break;
    }
  }
  else if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_LEFT:
      case SDL_SCANCODE_A:
        moveLeft = false;
        break;
      case SDL_SCANCODE_RIGHT:
      case SDL_SCANCODE_D:
        moveRight = false;
        break;
      case SDL_SCANCODE_SPACE:
        isShooting = false;
        break;
      default:
        // Unhandled keys are ignored
        break;
    }
  }

  // Debug output to verify key events are being received
  if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
    std::cout << "Key event: " << (event.type == SDL_KEYDOWN ? "DOWN" : "UP")
              << " scancode: " << event.key.keysym.scancode << std::endl;
  }
}

/**
 * @brief Updates the player’s position, input state, shooting, and bullets.
 *
 * @param deltaTime Time since last update in seconds.
 */
void Player::update(float deltaTime) {
  // Reset velocity
  velocity.x = 0.0f;

  // Apply movement based on key states
  if (moveLeft) {
    velocity.x = -moveSpeed;
  }

  if (moveRight) {
    velocity.x = moveSpeed;
  }

  // Update position based on velocity
  position.x += velocity.x * deltaTime;

  // Constrain player to screen boundaries
  position.x = std::max(width * 0.5f, std::min(position.x, 800.0f - width * 0.5f));

  // Handle shooting
  if (isShooting && shootCooldown <= 0.0f) {
    shoot();
  }

  // Update shoot cooldown
  if (shootCooldown > 0.0f) {
    shootCooldown -= deltaTime;
  }

  // Update bullets
  updateBullets(deltaTime);
}

/**
 * @brief Renders the player’s ship and its bullets.
 *
 * Draws the body as a rectangle and a triangular "nose" for style.
 */
void Player::render() {
  // Draw player ship as a simple rectangle
  Color playerColor(0, 255, 0);  // Green
  //
  SDL_FRect playerRect = {
    position.x - width * 0.5f,
    position.y - height * 0.5f,
    width,
    height
  };

  graphics->drawRect(playerRect, playerColor, true);

  // Draw a triangle on top to make it look like a ship
  float triangleHeight = height * 0.5f;
  graphics->drawLine(
    position.x, position.y - height * 0.5f - triangleHeight,
    position.x - width * 0.5f, position.y - height * 0.5f,
    playerColor
  );
  graphics->drawLine(
    position.x, position.y - height * 0.5f - triangleHeight,
    position.x + width * 0.5f, position.y - height * 0.5f,
    playerColor
  );

  // Render bullets
  for (auto& bullet : bullets) {
    bullet->render();
  }
}

/**
 * @brief Resets the player to default state and position.
 *
 * Resets position, lives, velocity, cooldown, and clears bullets.
 */
void Player::reset() {
  // Reset player state
  lives = 3;
  position.x = 400.0f;
  position.y = 550.0f;
  velocity.x = 0.0f;
  velocity.y = 0.0f;
  shootCooldown = 0.0f;

  // Clear bullets
  bullets.clear();

  moveLeft = false;
  moveRight = false;
  isShooting = false;
}

/**
 * @brief Decreases the player’s life count by one.
 */
void Player::takeDamage() {
  lives--;
}

/**
 * @brief Fires a bullet if no other bullet is on screen and cooldown is zero.
 *
 * Positions the bullet at the top center of the player and sets upward velocity.
 */
void Player::shoot() {
  // Multiple bullets
  // if (shootCooldown <= 0.0f) {
  // Multiple bullets no spamming
  // const size_t maxBullets = 3;
  // if (bullets.size() < maxBullets && shootCooldown <= 0.0f) {
  // Only allow one bullet at a time (like the original game)
  if (bullets.empty() && shootCooldown <= 0.0f) {
    auto bullet = std::make_unique<Bullet>(graphics);

    // Position the bullet at the top center of the player
    //float bulletX = position.x + (width / 2.0f) - (bullet->GetBounds().w / 2.0f);
    float bulletX = position.x;
    float bulletY = position.y - bullet->getBounds().h;

    bullet->setPosition(bulletX, bulletY);

    // Bullet travels upward
    bullet->setVelocity(0.0f, -500.0f);

    bullets.push_back(std::move(bullet));
    shootCooldown = 0.2f;
  }
}

