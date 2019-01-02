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
#define RATIO 16/9 /* Ratio de la résolution de l'écran */
#define BIT_PER_PIXEL 32 /* Nombre de bits par pixel de la fenêtre */

using namespace glimac;

static unsigned int FULLSCREEN = 0; /* 1 pour plein écran */


void resizeViewport() {
  // Taille du jeu, en fonction du ratio
  int maxHeight = WINDOW_HEIGHT;
  int maxWidth = round((float) maxHeight * RATIO);
  // Pixel en excès (contours noirs)
  int extraWidth = 0, extraHeight = 0;
  // L'inverse du ratio
  float reverseRatio = 1. / ((float) RATIO);

  /* Calcul de la taille du jeu par rapport à la fenêtre */
  if (maxWidth <= WINDOW_WIDTH) { // Trop large
    extraWidth = WINDOW_WIDTH - maxWidth;
  } else { // Pas assez large
    maxWidth = WINDOW_WIDTH;
    maxHeight = maxWidth * reverseRatio;
    extraHeight = WINDOW_HEIGHT - maxHeight;
  }
  glViewport(extraWidth / 2, extraHeight / 2, maxWidth, maxHeight);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluOrtho2D(-10., 10., -10.,10.);
  gluPerspective(60, (double)WINDOW_WIDTH/(double)WINDOW_HEIGHT, 1, 256);
  if (FULLSCREEN)
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE | SDL_FULLSCREEN);
  else
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
}

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

  /*SDL_Surface* surface = SDL_SetVideoMode(640, 480, 16, SDL_RESIZABLE);
  windowManager.toggle_fullscreen(surface);*/

  //surface = SDL_SetVideoMode(800, 600, 16, SDL_OPENGL);
std::cout << "sdl fine ! " << std::endl;
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
  Program program = loadProgram("shaders/triangle.vs.glsl",
                                "shaders/triangle.fs.glsl");
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
  FilePath menu = "assets/textures/menu.png";
  FilePath run = "assets/textures/run.png";
  FilePath replay = "assets/textures/replay.png";
  FilePath quit = "assets/textures/quit.png";

  Texture textureMenu(menu);
  Texture textureRun(run);
  Texture textureReplay(replay);
  Texture textureQuit(quit);

  vbo.bind();

  textureMenu.loadTexture();
  textureRun.loadTexture();

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
  //glVertexAttribPointer(GLuint index,GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
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
      if (e.button.x > 306 && e.button.x < 478 && e.button.y > 238 && e.button.y < 339)
      {
        mode = 2;
      }
      else if (e.button.x > 167 && e.button.x < 311 && e.button.y > 425 && e.button.y < 498)
      {
        mode = 0;
      }
      else if (e.button.x > 507 && e.button.x < 748 && e.button.y > 426 && e.button.y < 491)
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
          if (e.button.x > 167 && e.button.x < 311 && e.button.y > 425 && e.button.y < 498)
          {
            textureQuit.loadTexture();
            textureQuit.bind();
            done = true;
          }
          else if (e.button.x > 306 && e.button.x < 478 && e.button.y > 238 && e.button.y < 339)
          {
            std::cout << "PLAY ! RUN ! Game Begin ! " << std::endl;
            mode = 2;
          }
          else if (e.button.x > 507 && e.button.x < 748 && e.button.y > 426 && e.button.y < 491)
          {
            std::cout << "REPLAY ! RUN AGAIN ! Game Begin AGAIN ! " << std::endl;
            textureReplay.bind();
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
        resizeViewport();
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
      textureMenu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureMenu.debind();
    }
    else if (mode == 2)
    {
      textureRun.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureRun.debind();
    }
    else if (mode == 0)
    {
      textureQuit.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureQuit.debind();
    }
    else if (mode == 3)
    {
      textureReplay.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureReplay.debind();
    }
    windowManager.swapBuffers();
  }
  /*********************************
     *         EVENT CODE
     *********************************/
  textureMenu.free();

  //libération des ressources
  vbo.~VBO();
  vao.~VAO();

  return EXIT_SUCCESS;
}
