#include <Element/Stone.hpp>

void Stone::update() {
  // Stone rotation
  rotate(glm::vec3(0, m_rotationSpeed, 0));

  // Stone translation 
  if (std::abs(m_actualTranslate) >= m_maxTranslate)
    m_translateSpeed = -m_translateSpeed;
  m_actualTranslate += m_translateSpeed;

  Object::update();
}

glm::mat4 Stone::MWMatrix() const {
  glm::mat4 MWMatrix = glm::translate(glm::mat4(), m_position + m_actualTranslate);
  MWMatrix = glm::rotate(MWMatrix, m_rotation.x, glm::vec3(1.f, 0, 0));
  MWMatrix = glm::rotate(MWMatrix, m_rotation.y, glm::vec3(0, 1.f, 0));
  MWMatrix = glm::rotate(MWMatrix, m_rotation.z, glm::vec3(0, 0, 1.f));
  MWMatrix = glm::scale(MWMatrix, m_size);
  return MWMatrix;
}