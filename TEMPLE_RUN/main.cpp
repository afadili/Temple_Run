/**
 * \file main.cpp
 * \brief The main file of the game
 */

#include <glimac/SDLWindowManager.hpp>
#include <Game/GameManager.hpp>


// Nombre minimal de millisecondes separant le rendu de deux images
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
static const int WINDOWS_WIDTH = 800;
static const int WINDOWS_HEIGHT = 600;
static const float NEAR_VISION = 0.1f;
static const float FAR_VISION = 100.f;

/**
 * \brief ============================== main ==================================
 */

int main(int argc, char **argv) {
  // LOAD CONFIGURATION
  Configuration *config = new Configuration("data/config.json");

  // Initialize SDL and open a window
  SDLWindowManager windowManager(config->defaultWidth(), config->defaultWidth() * 1. / config->ratio(), "I N F I N I T Y   R U N");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if (GLEW_OK != glewInitError) {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/

  // GAME MANAGER
  GameManager manager(config);

  // activer le test de profondeur du GPU
  glEnable(GL_DEPTH_TEST);

  // Application loop:
  bool done = false;
  while (!done) {
    Uint32 startTime = SDL_GetTicks();

    // Event loop:
    SDL_Event e;
    while (windowManager.pollEvent(e)) {
      if (e.type == SDL_QUIT) {
        done = true; // Leave the loop after this iteration
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update the game
    manager.update(e);


    // Update the display
    windowManager.swapBuffers();

    // FPS CONTROLLER
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if (elapsedTime < 1000 / config->fps()) {
      SDL_Delay(1000 / config->fps() - elapsedTime);
    }
  }

  delete config;
  return EXIT_SUCCESS;
}