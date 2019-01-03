#include <Element/Object.hpp>

Object::Object(Mesh *mesh) : m_mesh(mesh) {
}

Object::Object(Mesh *mesh, const glm::vec3 &position) :
m_mesh(mesh), m_position(position) {
}

Object::Object(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size) :
m_mesh(mesh), m_position(position), m_size(size) {
}

Object::Object(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation) :
m_mesh(mesh), m_position(position), m_size(size), m_rotation(rotation) {
}

glm::mat4 Object::MWMatrix() const {
  glm::mat4 MWMatrix = glm::translate(glm::mat4(), m_position);
  MWMatrix = glm::rotate(MWMatrix, m_rotation.x, glm::vec3(1.f, 0, 0));
  MWMatrix = glm::rotate(MWMatrix, m_rotation.y, glm::vec3(0, 1.f, 0));
  MWMatrix = glm::rotate(MWMatrix, m_rotation.z, glm::vec3(0, 0, 1.f));
  MWMatrix = glm::scale(MWMatrix, m_size);
  return MWMatrix;
}

void Object::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix, const bool isBind) const {
  if (!isBind)
    m_mesh->bind();
  m_mesh->draw(ProjMatrix, MWMatrix(), ViewMatrix);
  if (!isBind)
    m_mesh->debind();
}