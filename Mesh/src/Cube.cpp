#include <GL/glew.h>
#include <glimac/common.hpp>
#include <Mesh/Cube.hpp>

Cube::Cube() : Mesh() {
  generateVertices(glm::vec3(1., 1., 1.));
  generateIndexs();
}

Cube::Cube(const glm::vec3 &size) : Mesh() {
  generateVertices(size);
  generateIndexs();
}

Cube::Cube(ShaderManager *shader, Texture *texture) : Mesh(shader, texture) {
  generateVertices(glm::vec3(1., 1., 1.));
  generateIndexs();
}

Cube::Cube(const glm::vec3 &size, ShaderManager *shader, Texture *texture) : Mesh(shader, texture) {
  generateVertices(size);
  generateIndexs();
}

void Cube::generateVertices(const glm::vec3 &size) {
  // Center the mesh 
  glm::vec3 upper = glm::vec3(size.x / 2., size.y / 2., size.z / 2.);
  glm::vec3 lower = glm::vec3(-size.x / 2., -size.y / 2., -size.z / 2.);

  // FRONT FACE                       		POSITION				NORMAL			TEXTURE
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, lower.y, upper.z), glm::vec3(lower.x, lower.y, upper.z), glm::vec2(0, 0))); // BOTTOM RIGHT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, lower.y, upper.z), glm::vec3(upper.x, lower.y, upper.z), glm::vec2(1, 0))); // BOTTOM LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, upper.y, upper.z), glm::vec3(upper.x, upper.y, upper.z), glm::vec2(1, 1))); // TOP LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, upper.y, upper.z), glm::vec3(lower.x, upper.y, upper.z), glm::vec2(0, 1))); // TOP RIGHT

  // RIGHT FACE                       		POSITION				NORMAL			TEXTURE
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, upper.y, upper.z), glm::vec3(upper.x, upper.y, upper.z), glm::vec2(0, 0))); // BOTTOM RIGHT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, upper.y, lower.z), glm::vec3(upper.x, upper.y, lower.z), glm::vec2(1, 0))); // BOTTOM LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, lower.y, lower.z), glm::vec3(upper.x, lower.y, lower.z), glm::vec2(1, 1))); // TOP LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, lower.y, upper.z), glm::vec3(upper.x, lower.y, upper.z), glm::vec2(0, 1))); // TOP RIGHT

  // BACK FACE                       		POSITION				NORMAL			TEXTURE
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, lower.y, lower.z), glm::vec3(lower.x, lower.y, lower.z), glm::vec2(0, 0))); // BOTTOM RIGHT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, lower.y, lower.z), glm::vec3(upper.x, lower.y, lower.z), glm::vec2(1, 0))); // BOTTOM LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, upper.y, lower.z), glm::vec3(upper.x, upper.y, lower.z), glm::vec2(1, 1))); // TOP LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, upper.y, lower.z), glm::vec3(lower.x, upper.y, lower.z), glm::vec2(0, 1))); // TOP RIGHT

  // LEFT FACE                       		POSITION				NORMAL			TEXTURE
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, lower.y, lower.z), glm::vec3(lower.x, lower.y, lower.z), glm::vec2(0, 0))); // BOTTOM RIGHT
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, lower.y, upper.z), glm::vec3(lower.x, lower.y, upper.z), glm::vec2(1, 0))); // BOTTOM LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, upper.y, upper.z), glm::vec3(lower.x, upper.y, upper.z), glm::vec2(1, 1))); // TOP LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, upper.y, lower.z), glm::vec3(lower.x, upper.y, lower.z), glm::vec2(0, 1))); // TOP RIGHT

  // UPPER FACE                       		POSITION				NORMAL			TEXTURE
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, upper.y, upper.z), glm::vec3(upper.x, upper.y, upper.z), glm::vec2(0, 0))); // BOTTOM RIGHT
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, upper.y, upper.z), glm::vec3(lower.x, upper.y, upper.z), glm::vec2(1, 0))); // BOTTOM LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, upper.y, lower.z), glm::vec3(lower.x, upper.y, lower.z), glm::vec2(1, 1))); // TOP LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, upper.y, lower.z), glm::vec3(upper.x, upper.y, lower.z), glm::vec2(0, 1))); // TOP RIGHT

  // BOTTOM FACE                       		POSITION				NORMAL			TEXTURE
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, lower.y, lower.z), glm::vec3(lower.x, lower.y, lower.z), glm::vec2(0, 0))); // BOTTOM RIGHT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, lower.y, lower.z), glm::vec3(upper.x, lower.y, lower.z), glm::vec2(1, 0))); // BOTTOM LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(upper.x, lower.y, upper.z), glm::vec3(upper.x, lower.y, upper.z), glm::vec2(1, 1))); // TOP LEFT
  m_vertices.push_back(ShapeVertex(glm::vec3(lower.x, lower.y, upper.z), glm::vec3(lower.x, lower.y, upper.z), glm::vec2(0, 1))); // TOP RIGHT
}

void Cube::generateIndexs() {
  m_indexVer.insert(m_indexVer.end(),{0, 1, 2, 0, 2, 3}); // FRONT FACE
  m_indexVer.insert(m_indexVer.end(),{4, 5, 6, 4, 6, 7}); // RIGHT FACE
  m_indexVer.insert(m_indexVer.end(),{8, 9, 10, 8, 10, 11}); // BACK FACE
  m_indexVer.insert(m_indexVer.end(),{12, 13, 14, 12, 14, 15}); // LEFT FACE
  m_indexVer.insert(m_indexVer.end(),{16, 17, 18, 16, 18, 19}); // TOP FACE
  m_indexVer.insert(m_indexVer.end(),{20, 21, 22, 20, 22, 23}); // BOTTOM FACE
}