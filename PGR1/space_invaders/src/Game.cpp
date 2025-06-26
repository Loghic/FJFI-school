/**
 * @file Game.cpp
 * @brief Implements the main game loop, initialization, event handling,
 *        updates, rendering, and collision detection for the Space Invaders game.
 *
 * This file handles the lifecycle of the game, including entity management,
 * score tracking, level progression, input, and game state transitions.
 */

#include "Game.h"
#include "Graphics.h"
#include "TextRenderer.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "Entities/Bullet.h"
#include "Entities/UFO.h"
#include "Barrier.h"

#include <SDL_events.h>
#include <SDL_rect.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>

/**
 * @brief Constructor for Game.
 *
 * @param window SDL window handle.
 * @param renderer SDL renderer handle.
 */
Game::Game(SDL_Window* window, SDL_Renderer* renderer)
  : window(window), renderer(renderer) {
}

/**
 * @brief Destructor for Game.
 *
 * Cleans up resources. Most cleanup is handled by smart pointers.
 */
Game::~Game() {
  // Cleanup happens in the member destructors
}

/**
 * @brief Initializes game components like player, enemies, barriers, and UI.
 */
void Game::initialize() {
  // Create graphics
  Graphics* graphics = new Graphics(renderer);

  // Create text renderer
  textRenderer = std::make_unique<TextRenderer>(graphics, renderer);

  // Attempt to load a font (falls back to primitive rendering if not found)
  textRenderer->loadFont("assets/DejaVuSans.ttf", 24);

  // Create player
  player = std::make_unique<Player>(graphics);
  player->setPosition(400.0f, 550.0f);

  // Create barriers
  createBarriers();

  // Create UFO
  ufo = std::make_unique<UFO>(new Graphics(renderer));

  // Initial enemy spawn
  spawnEnemies();

  // Ensure we start with game in progress, not game over
  gameOver = false;
  score = 0;
  level = 1;
}

/**
 * @brief Handles SDL input events.
 *
 * @param event SDL_Event object from SDL_PollEvent.
 */
void Game::handleEvent(const SDL_Event& event) {
  // Handle game-specific events
  if (event.type == SDL_KEYDOWN) {
    // In SDL3, key code handling is different
    if (event.key.keysym.scancode == SDL_SCANCODE_R && gameOver) {
        // Reset game on 'R' press when game over
        gameOver = false;
        if (score > highScore) {
            highScore = score;
        }
        score = 0;
        level = 1;
        enemies.clear();
        createBarriers(); // Recreate barriers
        spawnEnemies();
        player->reset();
        ufo->reset();
        hitFlashTimer = 0.0f; // reset red flash effect
    }

    // Take damage with T key (for testing)
    /*
    if (event.key.keysym.scancode == SDL_SCANCODE_T && !gameOver && player) {
      player->takeDamage();
      if (player->isDestroyed()) {
        gameOver = true;
        std::cout << "Game Over! Final Score: " << score << std::endl;
      }
    }
    */
  }

  // Pass events to player for handling
  if (!gameOver && player) {
      player->handleEvent(event);
  }
}

/**
 * @brief Updates all game objects and game state.
 *
 * @param deltaTime Time in seconds since last update.
 */
void Game::update(float deltaTime) {
  if (hitFlashTimer > 0.0f) {
    hitFlashTimer -= deltaTime;
  }

  if (gameOver || !player) {
    return;
  }

  gameTime += deltaTime;

  // Update player
  player->update(deltaTime);

  // Update enemies
  for (auto& enemy : enemies) {
    enemy->update(deltaTime, player->getPosition());
  }

  // Update barriers
  for (auto& barrier : barriers) {
    barrier->update(deltaTime);
  }

  // Update UFO
  if (ufo) {
    ufo->update(deltaTime);
  }

  // Remove destroyed enemies
  enemies.erase(
    std::remove_if(enemies.begin(), enemies.end(),
        [](const std::unique_ptr<Enemy>& enemy) { return enemy->isDestroyed(); }),
    enemies.end()
  );

  // Check for game over condition
  if (player->isDestroyed()) {
    gameOver = true;
    std::cout << "Game Over! Final Score: " << score << std::endl;
    return;
  }

  // Check if all enemies are destroyed
  if (enemies.empty()) {
    // Increase level and spawn new enemies
    level++;
    spawnEnemies();
    ufo->resetTimerOnly();
  }

  // Check for collisions
  checkCollisions();

  if (hitFlashTimer > 0.0f) {
    hitFlashTimer -= deltaTime;
  }
}

/**
 * @brief Renders the current score, high score, lives, and level.
 */
void Game::renderScore() {
  // Render score at the top of the screen
  std::stringstream ss;
  ss <<"LIVES:" << player->getLives() << "   SCORE: " << score <<
  "   HIGH SCORE: " << highScore << "   LEVEL: " << level;
  textRenderer->drawText(ss.str(), 400.0f, 20.0f, Color(255, 255, 255), true);
}

/**
 * @brief Renders all visual game components to the screen.
 */
void Game::render() {
  // Clear screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 30, 255);
  SDL_RenderClear(renderer);

  // Render player
  if (player && !player->isDestroyed()) {
    player->render();
  }

  // Render enemies
  for (auto& enemy : enemies) {
    enemy->render();
  }

  // Render barriers
  for (auto& barrier : barriers) {
    barrier->render();
  }

  // Render UFO
  if (ufo) {
    ufo->render();
  }

  // Render score
  renderScore();

  // Render game over message if needed
  if (gameOver) {
      // Game over overlay
      SDL_SetRenderDrawColor(renderer, 50, 0, 0, 180);
      SDL_Rect overlay = {0, 0, 800, 600};
      SDL_RenderFillRect(renderer, &overlay);

      // Game over text
      textRenderer->drawText("GAME OVER", 400.0f, 250.0f, Color(255, 255, 255), true);
      textRenderer->drawText("PRESS R TO RESTART", 400.0f, 300.0f, Color(255, 255, 255), true);

      std::stringstream ss;
      ss << "FINAL SCORE: " << score;
      textRenderer->drawText(ss.str(), 400.0f, 350.0f, Color(255, 255, 255), true);
    }

    // Present the rendered frame
    if (hitFlashTimer > 0.0f) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100); // partially see through red
      SDL_Rect border = {0, 0, 800, 600}; // whole screen
      SDL_RenderFillRect(renderer, &border);
    }
    SDL_RenderPresent(renderer);
}

/**
 * @brief Spawns a new wave of enemies based on current level.
 */
void Game::spawnEnemies() {
  const int rowCount = 3 + (level - 1) / 2; // More rows with higher levels
  const int colCount = 8;
  const float startX = 100.0f;
  const float startY = 50.0f;
  const float spacingX = 70.0f;
  const float spacingY = 50.0f;

  // Make sure we create a Graphics object that persists
  Graphics* graphics = new Graphics(renderer);

  for (int row = 0; row < rowCount; row++) {
    for (int col = 0; col < colCount; col++) {
      auto enemy = std::make_unique<Enemy>(graphics);
      enemy->setPosition(
          startX + col * spacingX,
          startY + row * spacingY
      );
      enemies.push_back(std::move(enemy));
    }
  }
}

/**
 * @brief Creates the defensive barriers in the game.
 */
void Game::createBarriers() {
  barriers.clear();

  // Create 4 barriers
  const int barrierCount = 4;
  const float barrierY = 450.0f;
  const float spacing = 160.0f;
  const float startX = 150.0f;

  for (int i = 0; i < barrierCount; i++) {
    float x = startX + i * spacing;
    barriers.push_back(std::make_unique<Barrier>(new Graphics(renderer), x, barrierY));
  }
}

/**
 * @brief Detects and resolves all game collisions.
 */
void Game::checkCollisions() {
  if (player == nullptr || gameOver) return;

  // Get player bullets
  const auto& playerBullets = player->GetBullets();

  // Check collision between player bullets and enemies
  for (auto& enemy : enemies) {
    for (auto& bullet : playerBullets) {
      if (!bullet->isDestroyed() && !enemy->isDestroyed()) {
        SDL_FRect bulletRect = bullet->getBounds();
        SDL_FRect enemyRect = enemy->getBounds();

        if (SDL_HasIntersectionF(&bulletRect, &enemyRect)) {
          enemy->destroy();
          bullet->destroy();
          score += 10 * level; // More points in higher levels
        }
      }
    }

    // Check collision between enemy and player (if enemy reaches bottom)
    if (!enemy->isDestroyed() && enemy->getPosition().y > 500) {
      player->destroy();
      gameOver = true;
    }

    // Check collision between enemy bullets and player
    const auto& enemyBullets = enemy->GetBullets();
    for (auto& bullet : enemyBullets) {
      if (!bullet->isDestroyed() && !player->isDestroyed()) {
        SDL_FRect bulletRect = bullet->getBounds();
        SDL_FRect playerRect = player->getBounds();

        if (SDL_HasIntersectionF(&bulletRect, &playerRect)) {
          player->takeDamage();
          bullet->destroy();
          hitFlashTimer = hitFlashDuration;
          if (player->isDestroyed()) {
            gameOver = true;
          }
        }
      }
      // Check collision between enemy bullets and barriers
      if (!bullet->isDestroyed()) {
        for (auto& barrier : barriers) {
          const auto& bricks = barrier->getBricks();
          SDL_FRect bulletRect = bullet->getBounds();

          for (size_t i = 0; i < bricks.size(); i++) {
            if (!bricks[i].destroyed) {
              if (SDL_HasIntersectionF(&bulletRect, &bricks[i].rect)) {
                barrier->damageBrick(i);
                bullet->destroy();
                break;
              }
            }
          }
        }
      }
    }

    // Check collision between player bullets and barriers
    for (auto& bullet : playerBullets) {
      if (!bullet->isDestroyed()) {
        for (auto& barrier : barriers) {
          const auto& bricks = barrier->getBricks();
          SDL_FRect bulletRect = bullet->getBounds();

          for (size_t i = 0; i < bricks.size(); i++) {
            if (!bricks[i].destroyed) {
              if (SDL_HasIntersectionF(&bulletRect, &bricks[i].rect)) {
                barrier->damageBrick(i);
                bullet->destroy();
                break;
              }
            }
          }
        }
      }
    }
    // Check collision between player bullets and UFO
    if (ufo && ufo->isActive() && !ufo->isDestroyed()) {
      for (auto& bullet : playerBullets) {
        if (!bullet->isDestroyed()) {
          SDL_FRect bulletRect = bullet->getBounds();
          SDL_FRect ufoRect = ufo->getBounds();

          if (SDL_HasIntersectionF(&bulletRect, &ufoRect)) {
              ufo->destroy();
              bullet->destroy();
              score += ufo->getScoreValue() * level;
          }
        }
      }
    }
  }
}
