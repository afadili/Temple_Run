/**
 * \file main.cpp
 * \brief The main file of the game
 */

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <Game/GameManager.hpp>
#include <Game/Level.hpp>
#include <Mesh/Cube.hpp>
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>


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
  // TEST GAME MANAGER
  //GameManager manager("TEMPLE_RUN/assets.json");


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

  //TEST PPM
  /* static const FilePath file = "../Levels/Tests/test3.ppm";
   Game gm(file, 1);
   gm.loadFloor(file, 0);*/


  // ======== TEST CUBE ========

  // Construct cube
  ShaderManager shaderCube("shaders/tex3D.vs.glsl", "shaders/tex3D.fs.glsl");
  shaderCube.use();
  shaderCube.addUniform("uMVPMatrix");
  shaderCube.addUniform("uMVMatrix");
  shaderCube.addUniform("uNormalMatrix");
  shaderCube.addUniform("uTexture");

  Texture textureCube("assets/textures/stone_wall.jpg");
  Cube myCube(glm::vec3(2), &shaderCube, &textureCube);

  // Cube Initilisation
  textureCube.loadTexture();
  myCube.fillBuffers();



  // END CUBE

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

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    // MATRICES de transformations
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOWS_WIDTH / (float) WINDOWS_HEIGHT, NEAR_VISION, FAR_VISION);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
    MVMatrix = glm::rotate(MVMatrix, windowManager.getTime() * 0.75f, glm::vec3(1.f, 1.f, 1.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    myCube.bind();
    myCube.draw(ProjMatrix, MVMatrix);
    myCube.debind();

    // Update the display
    windowManager.swapBuffers();
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if (elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  textureCube.free();


  return EXIT_SUCCESS;
}