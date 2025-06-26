/**
 * @file Barrier.cpp
 * @brief Implements the Barrier class used to represent destructible shields in the game.
 *
 * Each barrier consists of multiple small bricks that can be individually destroyed.
 * Barriers are static and are drawn using the SDL graphics backend.
 */
#include "Barrier.h"

/**
 * @brief Constructs a Barrier object at a given position and initializes its bricks.
 *
 * @param graphics Pointer to the Graphics object used for rendering.
 * @param x X-coordinate of the center of the barrier.
 * @param y Y-coordinate of the center of the barrier.
 */
Barrier::Barrier(Graphics* graphics, float x, float y) : graphics(graphics) {
  position.x = x;
  position.y = y;
  createBricks();
}

/**
 * @brief Destructor for the Barrier.
 */
Barrier::~Barrier() {
}

/**
 * @brief Updates the barrier state.
 *
 * Currently unused, as barriers are static and do not change over time.
 *
 * @param deltaTime Time elapsed since the last frame (unused).
 */
void Barrier::update(float deltaTime) {
  // Barriers are static, so no update logic needed
}

/**
 * @brief Renders the barrier by drawing all non-destroyed bricks.
 */
void Barrier::render() {
  Color barrierColor(0, 200, 0);  // Dark green

  // Render each brick that's not destroyed
  for (const auto& brick : bricks) {
    if (!brick.destroyed) {
      graphics->drawRect(brick.rect, barrierColor, true);
    }
  }
}

/**
 * @brief Creates the individual bricks that make up the barrier.
 *
 * The bricks are arranged in a rectangular shape, with an inverted-U cutout at the bottom center.
 */
void Barrier::createBricks() {
  // Create a rectangular barrier made of smaller bricks
  const int rows = (int)(height / brickSize);
  const int cols = (int)(width / brickSize);

  // Create a barrier shape (inverted U)
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      // Skip bricks to create an opening in the middle of the bottom row
      if (row == rows - 1 && col > cols/3 && col < 2*cols/3) {
        continue;
      }

      // Calculate brick position
      float brickX = position.x - width/2 + col * brickSize + brickSize/2;
      float brickY = position.y - height/2 + row * brickSize + brickSize/2;

      // Add the brick
      Brick brick;
      brick.rect = {
        brickX - brickSize/2,
        brickY - brickSize/2,
        brickSize,
        brickSize
      };
      brick.destroyed = false;
      bricks.push_back(brick);
    }
  }
}

/**
 * @brief Marks a specific brick as destroyed based on its index.
 *
 * @param index Index of the brick to destroy in the bricks vector.
 */
void Barrier::damageBrick(int index) {
  if (index >= 0 && index < (int)bricks.size()) {
    bricks[index].destroyed = true;
  }
}
