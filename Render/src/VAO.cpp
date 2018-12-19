#include <Render/VAO.hpp>

VAO::VAO() : Render() {
  glGenVertexArrays(1, &m_ID);
}

VAO::~VAO() {
  glDeleteVertexArrays(1, &m_ID);
}

void VAO::bind() const{
  glBindVertexArray(m_ID);
}

void VAO::debind() const{
  glBindVertexArray(0);
}

