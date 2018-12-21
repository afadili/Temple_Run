/**
 * \file main.cpp
 * \brief The main file of the game
 */

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <Game/GameManager.hpp>
#include <Game/Game.hpp>
#include <Mesh/Cube.hpp>
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>

#include <glimac/TrackballCamera.hpp>


// Nombre minimal de millisecondes separant le rendu de deux images
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
static const int WINDOWS_WIDTH = 800;
static const int WINDOWS_HEIGHT = 600;
static const float NEAR_VISION = 0.1f;
static const float FAR_VISION = 100.f;

/**
 * \brief ============================== main ==================================
 */

GLenum glCheckError_(const char *file, int line) {
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR) {
    std::string error;
    switch (errorCode) {
      case GL_INVALID_ENUM: error = "INVALID_ENUM";
        break;
      case GL_INVALID_VALUE: error = "INVALID_VALUE";
        break;
      case GL_INVALID_OPERATION: error = "INVALID_OPERATION";
        break;
      case GL_STACK_OVERFLOW: error = "STACK_OVERFLOW";
        break;
      case GL_STACK_UNDERFLOW: error = "STACK_UNDERFLOW";
        break;
      case GL_OUT_OF_MEMORY: error = "OUT_OF_MEMORY";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION";
        break;
    }
    std::cout << error << " | " << file << " (" << line << ")" << std::endl;
  }
  return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 


using namespace glimac;

int main(int argc, char **argv) {

  // Initialize SDL and open a window
  SDLWindowManager windowManager(800, 600, "I N F I N I T Y   R U N");

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

  // TEST GAME MANAGER
  GameManager manager("TEMPLE_RUN/assets.json");
  std::cout << "GAME MANAGER :\n" << manager << std::endl;

  //TEST PPM
  static const FilePath file = "../Levels/Tests/test2.ppm";
  Game gm(manager.assets(), file, 1);
  gm.loadFloor(file, 0);


  // activer le test de profondeur du GPU
  glEnable(GL_DEPTH_TEST);

  // Camera
  TrackballCamera camera;

  // Souris
  glm::ivec2 mousePos;
  glm::ivec2 lastMousePos;

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
      if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
        mousePos = windowManager.getMousePosition();
        camera.rotateLeft(mousePos.x - lastMousePos.x);
        camera.rotateUp(mousePos.y - lastMousePos.y);
        lastMousePos = mousePos;
      }
      if (windowManager.isKeyPressed(SDLK_UP))
        camera.moveFront(0.5);
      if (windowManager.isKeyPressed(SDLK_DOWN))
        camera.moveFront(-0.5);
    }

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    // MATRICES de transformations
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOWS_WIDTH / (float) WINDOWS_HEIGHT, NEAR_VISION, FAR_VISION);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gm.draw(ProjMatrix, camera.getViewMatrix());


    // Update the display
    windowManager.swapBuffers();
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if (elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }


  return EXIT_SUCCESS;
}