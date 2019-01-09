/**
 * \file main.cpp
 * \brief The main file of the game
 */

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <SDL/SDL.h>
#include <math.h>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <Game/GameManager.hpp>
#include <Render/VAO.hpp>
#include <glimac/glm.hpp>
#include <Game/Level.hpp>
#include <Mesh/Cube.hpp>
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>

#include <glimac/FreeflyCamera.hpp>
#define BIT_PER_PIXEL 32 /* Nombre de bits par pixel de la fenêtre */

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
  // Charger et compiler les shaders
  FilePath applicationPath(argv[0]);
  Program program = loadProgram("data/shaders/triangle.vs.glsl",
          "data/shaders/triangle.fs.glsl");
  program.use(); // Indiquer a OpenGL de les utiliser

  // Variable uniforme partagée par tous mes shaders
  GLint uTexture = glGetUniformLocation(program.getGLId(), "uTexture");

  // Création d'un seul VBO = contient les données
  VBO vbo;

  //Binding d'un VBO sur la cible GL_ARRAY_BUFFER: permet de la modifier
  vbo.bind();

  //On peut à présent modifier le VBO en passant par la cible
  /*
    // Création d'un Menu 
   // Menu principalMenu;
    principalMenu.CreateTextureMenu();

     vbo.bind();

     //Envoi des données
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);
    //On utilise GL_STATIC_DRAW pour un buffer dont les données ne changeront jamais.

    //Débindage, pour éviter de remodifier le VBO par erreur.
    vbo.debind();

    //Création du VAO (Vertex Array Object) = décrit les données
    //décrit pour chaque attribut de sommet (position, couleur, normale, etc.) la manière dont ils sont rangés dans un ou plusieurs VBOs
    VAO vao;
    vao.~VAO();

    //Binding du VAO
    vao.bind();

     //Activation des attributs de vertex
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TEXCOORDS = 1;
    const GLuint VERTEX_ATTR_COLOR = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    //Binding d'un VBO sur la cible GL_ARRAY_BUFFER:
    vbo.bind();

    //Spécification des attributs de vertex
  
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid *)offsetof(Vertex2DColor, position));
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid *)offsetof(Vertex2DColor, color));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid *)offsetof(Vertex2DColor, texCoords));

    //Débindage
    vbo.bind();
    glBindVertexArray(0);

    glClear(GL_COLOR_BUFFER_BIT);

    glUniform1i(uTexture, 0); // envoie de l'id de la texture à la variable uniforme sampler 2D

    vao.bind();
   */
  // TEST GAME MANAGER
  Configuration *config = new Configuration("data/config.json");
  GameManager manager(config);
  std::cout << "GAME MANAGER :\n" << manager << std::endl;

  manager.loadLevel("level2");


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

      //principalMenu.EventManager(e);

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

    //principalMenu.drawMenu();
    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    // MATRICES de transformations
    //glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOWS_WIDTH / (float) WINDOWS_HEIGHT, NEAR_VISION, FAR_VISION);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //manager.level()->draw(ProjMatrix, camera.getViewMatrix());

      // Update the game
    manager.update();


    // Update the display
    windowManager.swapBuffers();
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if (elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }
  //textureLevelmenu.free();

  //libération des ressources
  //vbo.~VBO();
  //vao.~VAO();

  delete config;
  return EXIT_SUCCESS;
}