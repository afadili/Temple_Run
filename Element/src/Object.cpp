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

glm::mat4 Object::positionMatrix() const {
  return glm::translate(glm::mat4(), m_position);
}

void Object::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix, const bool isBind) const {
  if (!isBind)
    m_mesh->bind();
  m_mesh->draw(ProjMatrix, MWMatrix(), ViewMatrix);
  if (!isBind)
    m_mesh->debind();
}

float Object::lastUpdate() const {
  if (m_lastUpdate != 0)
    return float(std::clock() - m_lastUpdate) / CLOCKS_PER_SEC;
  return 0;
}

const std::vector<int> Object::gridPosition() const {
  std::vector<int> vec;
  vec.push_back(std::floor(m_position.x));
  vec.push_back(std::floor(m_position.y));
  vec.push_back(std::floor(m_position.z));
  return vec;
}

const std::vector<int> Object::gridPosition(const int x, const int y, const int z) const {
  glm::vec3 pos = absolutePosition(glm::vec3(x, y, z));
  std::vector<int> vec;
  vec.push_back(pos.x);
  vec.push_back(pos.y);
  vec.push_back(pos.z);
  return vec;
}

glm::vec3 Object::absolutePosition(const glm::vec3 &vec) const {
  glm::vec3 pos = m_position;
  float orientation = std::fmod(m_rotation.y + 2. * M_PI, 2. * M_PI);

  if (orientation < M_PI / 2.) {
    pos.x += vec.x;
    pos.z += vec.z;
  } else if (orientation < M_PI) {
    pos.x += vec.z;
    pos.z += -vec.x;
  } else if (orientation < 3. * M_PI / 2.) {
    pos.x += -vec.x;
    pos.z += -vec.z;
  } else {
    pos.x += -vec.z;
    pos.z += vec.x;
  }
  pos.y += vec.y;
  return pos;
}

void Object::roundPosition(bool onX, bool onY, bool onZ) {
  if (onX)
    m_position.x = std::round(m_position.x);
  if (onY)
    m_position.y = std::round(m_position.y);
  if (onZ)
    m_position.z = std::round(m_position.z);
}