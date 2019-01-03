#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <Render/Texture.hpp>
#include <Render/VAO.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <SDL/SDL.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
//#define RATIO 16/9 /* Ratio de la résolution de l'écran */
#define BIT_PER_PIXEL 32 /* Nombre de bits par pixel de la fenêtre */

using namespace glimac;

static unsigned int FULLSCREEN = 0; /* 1 pour plein écran */

struct Vertex2DColor
{
  Vertex2DColor();
  Vertex2DColor(const glm::vec2 &vecPos, const glm::vec3 &vecCol, const glm::vec2 &vecTex) : position(vecPos), color(vecCol), texCoords(vecTex){}; // constructeur

  glm::vec2 position;
  glm::vec2 texCoords;
  glm::vec3 color;
};

int main(int argc, char **argv)
{
  // Initialize SDL and open a window
  SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "I N F I N I T Y   R U N");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if (GLEW_OK != glewInitError)
  {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   *      INITIALIZATION CODE
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

  int mode = 1;

  // Création d'une texture
  FilePath Levelmenu = "data/assets/textures/Levelmenu.png";
  FilePath Level1menu = "data/assets/textures/Level1menu.png";
  FilePath Level2menu = "data/assets/textures/Level2menu.png";
  FilePath Level3menu = "data/assets/textures/Level3menu.png";

  Texture textureLevelmenu(Levelmenu);
  Texture textureLevel1menu(Level1menu);
  Texture textureLevel2menu(Level2menu);
  Texture textureLevel3menu(Level3menu);

  vbo.bind();

  textureLevelmenu.loadTexture();
  textureLevel1menu.loadTexture();

  //Coordonnée quad
  Vertex2DColor vertices[] = {
      Vertex2DColor(glm::vec2(-1, -1), glm::vec3(1, 0, 0), glm::vec2(0, 1)),
      Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1, 1)),
      Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0, 0)),
      Vertex2DColor(glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec2(1, 0)),
      Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1, 1)),
      Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0, 0))};

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

  // Application loop:
  bool done = false;
  while (!done)
  {
    // Event loop:
    SDL_Event e;
    while (windowManager.pollEvent(e))
    {
      /* L'utilisateur ferme la fenêtre */
      if (e.type == SDL_QUIT)
      {
        done = true; // Leave the loop after this iteration
      }
      if (e.button.x > 261 && e.button.x < 538 && e.button.y > 239 && e.button.y < 310)
      {
        mode = 2;
      }
      else if (e.button.x > 252 && e.button.x < 539 && e.button.y > 345 && e.button.y < 415)
      {
        mode = 0;
      }
      else if (e.button.x > 243 && e.button.x < 532 && e.button.y > 450 && e.button.y < 520)
      {
        mode = 3;
      }
      else
      {
        mode = 1;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
          std::cout << "(" << e.button.x << "," << e.button.y << ")" << std::endl;
          //done = true;
          if (e.button.x > 243 && e.button.x < 532 && e.button.y > 450 && e.button.y < 520)
          {
            std::cout << "Level 3 ! " << std::endl;
          }
          else if (e.button.x > 261 && e.button.x < 538 && e.button.y > 239 && e.button.y < 310)
          {
            std::cout << "Level 1 ! " << std::endl;
            mode = 2;
          }
          else if (e.button.x > 252 && e.button.x < 539 && e.button.y > 345 && e.button.y < 415)
          {
            std::cout << "Level 2! " << std::endl;
          }
        }
      }
      /* Traitement d'evenements :*/
      switch (e.type)
      {
        /*Touche clavier*/
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_q:
          done = true;
          break;

        case SDLK_SPACE:
          std::cout << "PLAY ! " << std::endl;
          break;

        case SDLK_ESCAPE:
          done = true;
          break;

        case SDL_MOUSEBUTTONDOWN:
          if (e.button.button == SDL_BUTTON_LEFT)
          {
            std::cout << "(" << e.button.x << "," << e.button.y << ")" << std::endl;
            if (e.button.x > 170 && e.button.x < 335 && e.button.y > 325 && e.button.y < 500)
              done = true;
          }
          break;

        case SDL_VIDEORESIZE:
        e.resize.w = WINDOW_WIDTH;
        e.resize.h = WINDOW_HEIGHT;
        //resizeViewport();
        break;

        default:
          break;
        }
      }
    }
    /*********************************
     *         RENDERING CODE
     *********************************/

    if (mode == 1)
    {
      textureLevelmenu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureLevelmenu.debind();
    }
    else if (mode == 2)
    {
      textureLevel1menu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureLevel1menu.debind();
    }
    else if (mode == 0)
    {
      textureLevel2menu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureLevel2menu.debind();
    }
    else if (mode == 3)
    {
      textureLevel3menu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureLevel3menu.debind();
    }
    windowManager.swapBuffers();
  }
  /*********************************
     *         EVENT CODE
     *********************************/
  textureLevelmenu.free();

  //libération des ressources
  vbo.~VBO();
  vao.~VAO();

  return EXIT_SUCCESS;
}
