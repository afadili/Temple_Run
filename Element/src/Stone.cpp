#include <Element/Stone.hpp>

void Stone::update() {
  rotate(glm::vec3(0, m_rotationSpeed, 0));
}