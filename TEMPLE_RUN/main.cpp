/**
 * \file main.cpp
 * \brief The main file of the game
 */

#include <glimac/SDLWindowManager.hpp>
#include <Game/GameManager.hpp>
#include <glimac/FreeflyCamera.hpp>


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


  // Camera
  FreeflyCamera camera;


  // Keyboard
  bool KEY_UP_PRESSED = false;
  bool KEY_DOWN_PRESSED = false;
  bool KEY_LEFT_PRESSED = false;
  bool KEY_RIGHT_PRESSED = false;


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

      switch (e.type) {
          /* Touche clavier DOWN */
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP) {
            KEY_UP_PRESSED = true;
          }
          if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN) {
            KEY_DOWN_PRESSED = true;
          }
          if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_LEFT) {
            KEY_LEFT_PRESSED = true;
          }
          if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) {
            KEY_RIGHT_PRESSED = true;
          }
          break;


        case SDL_KEYUP:
          if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP) {
            KEY_UP_PRESSED = false;
          }
          if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN) {
            KEY_DOWN_PRESSED = false;
          }
          if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_LEFT) {
            KEY_LEFT_PRESSED = false;
          }
          if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) {
            KEY_RIGHT_PRESSED = false;
          }
          break;

        case SDL_MOUSEBUTTONDOWN:
          if (e.button.button == SDL_BUTTON_LEFT) {
            std::cout << "(" << e.button.x << "," << e.button.y << ")" << std::endl;
            if (e.button.x > 170 && e.button.x < 335 && e.button.y > 325 && e.button.y < 500)
              done = true;
          }
          break;

        case SDL_MOUSEMOTION:
          float speed = 0.5f;
          if (e.motion.xrel != 0) {
            camera.rotateLeft(float(-e.motion.xrel) * speed);
          }
          if (e.motion.yrel != 0) {
            camera.rotateUp(float(e.motion.yrel) * speed);
          }
          break;
      }
    }

    /* CONTROL */

    float speed = 0.1f;
    if (KEY_UP_PRESSED) {
      camera.moveFront(speed);
    } else if (KEY_DOWN_PRESSED) {
      camera.moveFront(-speed);
    } else if (KEY_LEFT_PRESSED) {
      KEY_LEFT_PRESSED = true;
      camera.moveLeft(speed);
    } else if (KEY_RIGHT_PRESSED) {
      KEY_RIGHT_PRESSED = true;
      camera.moveLeft(-speed);
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