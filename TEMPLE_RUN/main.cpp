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


/**
 * \brief ============================== main ==================================
 */

using namespace glimac;

// Nombre minimal de millisecondes separant le rendu de deux images
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char **argv) {
  // TEST GAME MANAGER
  GameManager manager("TEMPLE_RUN/assets.json");


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
  static const FilePath file = "../Levels/Tests/test3.ppm";
  Game gm(file, 1);
  gm.loadFloor(file, 0);


  // ======== TEST CUBE ========

  // Construct cube
  ShaderManager shaderCube("TEMPLE_RUN/shaders/tex3D.vs.glsl", "TEMPLE_RUN/shaders/tex3D.fs.glsl");
  shaderCube.addUniform("uMVPMatrix");
  shaderCube.addUniform("uMVMatrix");
  shaderCube.addUniform("uNormalMatrix");

  Texture textureCube("TEMPLE_RUN/assets/textures/triforce.png");
  Cube myCube(glm::vec3(10), &shaderCube, &textureCube);

  // Cube Initilisation
  textureCube.loadTexture();
  myCube.fillBuffers();

  // TMP 
  /* 5-8_ Création des matrices de Projection, MV et Normales */
  glm::mat4 ProjMatrix, MVMatrix, NormalMatrix, globalMVMatrix;
  ProjMatrix = glm::perspective(glm::radians(70.0f), // Angle vertical de vue
          (float) (800 / 600), // Ratio de la fenetre
          0.1f, // Near
          100.f); // Far
  MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -5));
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
  globalMVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -5));

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
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind du VAO
    myCube.vao().bind();

    // program du shader
    myCube.shader()->use();

    // variables uniformes
    glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
    myCube.shader()->sendUniformMatrix4fv("uMVMatrix", earthMVMatrix);
    myCube.shader()->sendUniformMatrix4fv("uNormalMatrix", glm::transpose(glm::inverse(earthMVMatrix)));
    myCube.shader()->sendUniformMatrix4fv("uMVPMatrix", ProjMatrix * earthMVMatrix);
    myCube.shader()->sendUniform1i("uTexture", 0);

    // bind de la texture
    myCube.texture()->bind();

    // draw
    glDrawArrays(GL_TRIANGLES, 0, myCube.vertexCount());


    // debind de la texture
    myCube.texture()->unbind();


    // debind du VAO
    myCube.vao().debind();

    // Update the display
    windowManager.swapBuffers();
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if (elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  return EXIT_SUCCESS;
}