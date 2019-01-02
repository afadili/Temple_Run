#include <Element/Stone.hpp>

void Stone::update() {
  // Stone rotation
  rotate(glm::vec3(0, m_rotationSpeed, 0));

  // Stone translation 
  if (std::abs(m_actualTranslate) >= m_maxTranslate)
    m_translateSpeed = -m_translateSpeed;
  m_actualTranslate += m_translateSpeed;
  translate(glm::vec3(0, m_translateSpeed, 0));
}