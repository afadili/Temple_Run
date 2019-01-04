#include <Game/Camera.hpp>

Camera::Camera() : m_fDistance(-15.0f), m_fAngleX(0.0f), m_fAngleY(0.0f), m_center(0.f, 0.f, 0.f) {
  computeDirectionVectors();
};

void Camera::moveUp() {
}

void Camera::moveForward(const float &x) {
  if (x > 0 && m_center >= -1.0f)
    return;
  m_center += x;
}

void Camera::moveLeft(const float &x) {
  m_rotateX += x;
}

void Camera::moveRight(const float &y) {
  m_rotateY += y;
}

void Camera::readEvent(const SDL_Event &e) {
  switch (e.type) {
      // Touche du clavier
    case SDL_KEYDOWN:
    {
      float step = 1.0f;
      if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP) // touche de Haut
      {
        moveForward(step);
      } else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN) // touche de bas 
      {
        moveForward(-step);
      }
    }
      break;
      // la souris 
    case SDL_MOUSEMOTION:
    {
      float speed = 1.f;
      if (e.motion.xrel != 0) {
        moveRight(float(e.motion.xrel) * speed);
      }
      if (e.motion.yrel != 0) {
        moveLeft(float(e.motion.yrel) * speed);
      }

    }
      break;

    default:
      break;
  }
}

glm::mat4 Camera::getViewMatrix() const {
  glm::mat4 VM = glm::mat4(1.f);
  VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, m_center));
  VM = glm::rotate(VM, glm::radians(m_rotateX), glm::vec3(1.0f, 0.0f, 0.0f));
  VM = glm::rotate(VM, glm::radians(m_rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
  VM = glm::translate(VM, -m_position);
  return VM;

}