#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>

using namespace glimac;

struct Vertex2DColor{
  Vertex2DColor(); 
  Vertex2DColor(const glm::vec2 &vecPos, const glm::vec3 &vecCol, const glm::vec2 &vecTex) : position(vecPos), color(vecCol), texCoords(vecTex){}; // constructeur

  glm::vec2 position;
  glm::vec2 texCoords;
  glm::vec3 color;
};

int main(int argc, char** argv) {
  // Initialize SDL and open a window
  SDLWindowManager windowManager(800, 600, "GLImac");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if (GLEW_OK != glewInitError) {
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
  GLuint vbo;
  glGenBuffers(1, &vbo);

  //Binding d'un VBO sur la cible GL_ARRAY_BUFFER: permet de la modifier
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  //On peut à présent modifier le VBO en passant par la cible 

  // Création d'une texture 
  std::unique_ptr<Image> menuMap = loadImage("TEMPLE_RUN/assets/textures/menu.png"); // il faut faire une fonction qui donne le chemin absolu à partir du chemin relatif peut etre existe dans glimac

  if (menuMap == NULL)
  	{
  		std::cerr << "t'as fais de la merde ! " << std::endl;
  		exit(0);
  	}


  	GLuint textureMenu;

  	glBindBuffer(GL_ARRAY_BUFFER, vbo);

  	// on génère une texture 
  	glGenTextures(1,&textureMenu);

  	 glBindTexture(GL_TEXTURE_2D, textureMenu);
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            menuMap->getWidth(),
            menuMap->getHeight(),
            0,
            GL_RGBA,
            GL_FLOAT,
            menuMap->getPixels());
        glTexParameteri(GL_TEXTURE_2D, 
            GL_TEXTURE_MIN_FILTER, 
            GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, 
            GL_TEXTURE_MAG_FILTER, 
            GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D,0);


  //Coordonnée quad
  Vertex2DColor vertices[] = { 
    Vertex2DColor(glm::vec2(-1, -1), glm::vec3(1, 0, 0), glm::vec2(0,1)),
    Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1,1)),
    Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0,0)),
    Vertex2DColor(glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec2(1,0)),
    Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1,1)),
    Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0,0))
  };

  //Envoi des données
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof (Vertex2DColor), vertices, GL_STATIC_DRAW);
  //On utilise GL_STATIC_DRAW pour un buffer dont les données ne changeront jamais.

  //Débindage, pour éviter de remodifier le VBO par erreur.
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //Création du VAO (Vertex Array Object) = décrit les données
  //décrit pour chaque attribut de sommet (position, couleur, normale, etc.) la manière dont ils sont rangés dans un ou plusieurs VBOs
  GLuint vao;
  glGenVertexArrays(1, &vao);

  //Binding du VAO
  glBindVertexArray(vao);

  //Activation des attributs de vertex
  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_TEXCOORDS = 1;
  const GLuint VERTEX_ATTR_COLOR = 2;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
  glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

  //Binding d'un VBO sur la cible GL_ARRAY_BUFFER:
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  //Spécification des attributs de vertex
  //glVertexAttribPointer(GLuint index,GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
  glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, position));
  glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, color));
  glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, texCoords));


  //Débindage
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  // Application loop:
  bool done = false;
  while (!done) {
    // Event loop:
    SDL_Event e;
    while (windowManager.pollEvent(e)) {
      if (e.type == SDL_QUIT) {
        done = true; // Leave the loop after this iteration
      }
    }

    /*********************************
     *         RENDERING CODE
     *********************************/
    //glClear(GLbitfield mask);
    glClear(GL_COLOR_BUFFER_BIT);

    glUniform1i(uTexture,0); // envoie de l'id de la texture à la variable uniforme sampler 2D

    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureMenu);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
    // Update the display
    windowManager.swapBuffers();
  }

  //libération des ressources
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  return EXIT_SUCCESS;
}
