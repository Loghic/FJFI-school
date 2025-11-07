/**
 * @file main.cpp
 * @brief Entry point for the Space Invaders game application.
 *
 * This file initializes the SDL library, creates a window and renderer,
 * shows a welcome screen, and runs the main game loop until the user quits.
 *
 * Features include:
 * - SDL initialization and cleanup
 * - Window and renderer creation with error handling
 * - Welcome screen display with text rendering and input detection
 * - Game object initialization and main loop handling events, updates, and rendering
 * - Frame rate control and delta time calculation for smooth gameplay
 *
 * Dependencies:
 * - SDL2 (SDL.h, SDL_render.h, SDL_video.h)
 * - Game class (Game.h)
 * - TextRenderer class
 */

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>
#include "Game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/**
 * @brief Main entry point of the application.
 *
 * Initializes SDL video subsystem, creates window and renderer,
 * displays a welcome screen waiting for user input, then enters
 * the main game loop which processes events, updates the game state,
 * and renders frames until the user quits.
 *
 * @param argc Argument count (unused).
 * @param argv Argument vector (unused).
 * @return int Exit status code.
 */
int main(int argc, char* argv[]) {
  // Initialise SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    std::cerr << "SDL could not initialise! SDL_Error: "
              <<  SDL_GetError() << std::endl;
    return -1;
  }

  // Create window
  SDL_Window* window = SDL_CreateWindow(
    "Space Invaders",
    SDL_WINDOWPOS_CENTERED, // x
    SDL_WINDOWPOS_CENTERED, // y
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN // flags
  );

  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: "
              << SDL_GetError() << std::endl;
    return -1;
  }

  // Create renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window,
                                              -1, // first rendering driver
                                              SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL_Error: "
              << SDL_GetError() << std::endl;
    return -1;
  }

  // Show welcome screen
  TextRenderer welcomeText(nullptr, renderer); // no Graphics* needed
  welcomeText.loadFont("assets/DejaVuSans.ttf", 36);
  bool startGame = false;
  while (!startGame) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
      }
      if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
        startGame = true;
      }
    }

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw welcome text
    welcomeText.drawText("SPACE INVADERS", SCREEN_WIDTH / 2.0f, 200, {255, 255, 255, 255}, true);
    welcomeText.drawText("Press any key to start", SCREEN_WIDTH / 2.0f, 300, {200, 200, 200, 255}, true);


    SDL_RenderPresent(renderer);
    SDL_Delay(16); // ~60 FPS
  }

  // Initialise game
  Game game(window, renderer);
  game.initialize();

  // Main game loop
  bool quit = false;
  SDL_Event event;
  Uint64 lastTime = SDL_GetTicks();

  while(!quit) {
    // Handle events
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        quit = true;
      }
      game.handleEvent(event);
    }

    // Calculate delta time
    Uint64 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    // Give delta time minumum value, else it might be 0, breaks the physics
    // if (deltaTime <= 0.001f){
    //   deltaTime = 0.001f;
    // }
    // Cap delta time to prevent physics issues on lag spikes
    if (deltaTime >= 0.0f) {
      deltaTime = 0.05f;
    }

     const float slowFactor = 0.5f;
     deltaTime *= slowFactor;

    // Update and render
    game.update(deltaTime);
    game.render();

    // Delay to cap framerate if needed
    SDL_Delay(1);
  }

  // Cleanup
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

