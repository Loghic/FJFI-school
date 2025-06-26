#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Graphics.h"

/**
 * @class Barrier
 * @brief Represents a barrier composed of multiple destructible bricks.
 *
 * Each brick can be damaged and destroyed individually. The barrier can be updated and rendered.
 */
class Barrier {
public:
  /**
   * @brief Constructs a barrier at the specified position.
   * @param graphics Pointer to the graphics context for rendering.
   * @param x The x-coordinate of the barrier's position.
   * @param y The y-coordinate of the barrier's position.
   */
  Barrier(Graphics* graphics, float x, float y);

  /** Destructor */
  ~Barrier();

  /**
   * @brief Updates the barrier state.
   * @param deltaTime Time elapsed since the last update (in seconds).
   */
  void update(float deltaTime);

  /**
   * @brief Renders the barrier by drawing all non-destroyed bricks.
   */
  void render();

  /**
   * @struct Brick
   * @brief Represents an individual brick in the barrier.
   */
  struct Brick {
    SDL_FRect rect;
    bool destroyed = false;
  };

   /**
   * @brief Gets a constant reference to the vector of bricks.
   * @return Reference to the list of bricks.
   */
  const std::vector<Brick>& getBricks() const { return bricks; }

  /**
   * @brief Damages (destroys) the brick at the given index.
   * @param index The index of the brick to damage.
   */
  void damageBrick(int index);

  /**
   * @brief Gets the position of the barrier.
   * @return The (x, y) position as an SDL_FPoint.
   */
  SDL_FPoint getPosition() const { return position; }

private:
  Graphics* graphics;               ///< Graphics context for rendering.
  SDL_FPoint position{0.0f, 0.0f};  ///< Position of the barrier.

  float width = 80.0f;              ///< Total width of the barrier.
  float height = 60.0f;             ///< Total height of the barrier.
  float brickSize = 10.0f;          ///< Size of each individual brick.

  std::vector<Brick> bricks;        ///< Vector holding all bricks composing the barrier.

  /**
   * @brief Initializes the bricks that compose the barrier.
   */
  void createBricks();
};
