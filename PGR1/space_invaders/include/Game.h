#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "TextRenderer.h" // Font-based TextRenderer

// Forward declarations
class Player;
class Enemy;
class Bullet;
class Barrier;
class UFO;

/**
 * @class Game
 * @brief Manages the overall game state, entities, and game loop logic.
 *
 * This class handles initialization, input processing, updating game state,
 * rendering, and managing game entities such as player, enemies, barriers, and UFO.
 */
class Game {
public:
  /**
   * @brief Constructs the game with a given SDL window and renderer.
   * @param window Pointer to the SDL window.
   * @param render Pointer to the SDL renderer.
   */
  Game(SDL_Window* window, SDL_Renderer* render);

  /** Destructor */
  ~Game();

  /**
   * @brief Initializes game components, entities, and resources.
   */
  void initialize();

  /**
   * @brief Processes incoming SDL events such as input.
   * @param event The SDL_Event to handle.
   */
  void handleEvent(const SDL_Event& event);

  /**
   * @brief Updates game state, entities, and timers.
   * @param deltaTime Time elapsed since last update (seconds).
   */
  void update(float deltaTime);

  /**
   * @brief Renders all game elements to the screen.
   */
  void render();

private:
  SDL_Window* window;                               ///< Pointer to the SDL window.
  SDL_Renderer* renderer;                           ///< Pointer to the SDL renderer.

  std::unique_ptr<Player> player;                   ///< Player entity.
  std::vector<std::unique_ptr<Enemy>> enemies;      ///< List of enemy entities.
  std::vector<std::unique_ptr<Barrier>> barriers;   ///< List of barrier entities.
  std::unique_ptr<UFO> ufo;                         ///< UFO entity.

  std::unique_ptr<TextRenderer> textRenderer;       ///< Renderer for displaying text such as scores.

  float gameTime = 0.0f;                            ///< Total elapsed game time in seconds.

  // Game state flags and counters
  bool gameOver = false;                            ///< Whether the game has ended.
  int score = 0;                                    ///< Current player score.
  int highScore = 0;                                ///< Highest score achieved.
  int level = 1;                                    ///< Current game level.

  // Timing parameters for spawning enemies
  const float enemySpawnTime = 5.0f;                ///< Time interval between enemy spawns.
  float enemySpawnTimer = 0.0f;                     ///< Timer tracking enemy spawn intervals.

  float hitFlashTimer = 0.0f; /// How long should the effect be active
  const float hitFlashDuration = 0.2f; /// 200ms duration of the red effect

  /**
   * @brief Spawns enemy entities into the game.
   */
  void spawnEnemies();

  /**
   * @brief Spawns enemy entities into the game.
   */
  void createBarriers();

  /**
   * @brief Checks and resolves collisions between entities.
   */
  void checkCollisions();

  /**
   * @brief Renders the player's current score and other UI text.
   */
  void renderScore();
};

