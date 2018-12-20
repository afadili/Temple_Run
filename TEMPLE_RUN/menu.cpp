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

using namespace glimac;

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
  SDLWindowManager windowManager(800, 600, "GLImac");

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
  Program program = loadProgram("TEMPLE_RUN/shaders/triangle.vs.glsl",
                                "TEMPLE_RUN/shaders/triangle.fs.glsl");
  program.use(); // Indiquer a OpenGL de les utiliser

  // Variable uniforme partagée par tous mes shaders
  GLint uTexture = glGetUniformLocation(program.getGLId(), "uTexture");

  // Création d'un seul VBO = contient les données
  VBO vbo;

  //Binding d'un VBO sur la cible GL_ARRAY_BUFFER: permet de la modifier
  vbo.bind();

  //On peut à présent modifier le VBO en passant par la cible

  // Création d'une texture

  Texture textureMenu("TEMPLE_RUN/assets/textures/menu.png");

  vbo.bind();

  textureMenu.loadTexture();
  
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

  // Application loop:
  bool done = false;
  while (!done)
  {
    // Event loop:
    SDL_Event e;
    while (windowManager.pollEvent(e))
    {
      if (e.type == SDL_QUIT)
      {
        done = true; // Leave the loop after this iteration
      }
    }

    /*********************************
     *         RENDERING CODE
     *********************************/
    //glClear(GLbitfield mask);
    glClear(GL_COLOR_BUFFER_BIT);

    glUniform1i(uTexture, 0); // envoie de l'id de la texture à la variable uniforme sampler 2D

    vao.bind();

    textureMenu.bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    textureMenu.debind();

    windowManager.swapBuffers();
  }

  textureMenu.free();

  //libération des ressources
  vbo.~VBO();
  vao.~VAO();

  return EXIT_SUCCESS;
}
