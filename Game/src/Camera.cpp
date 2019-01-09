#include <Game/Camera.hpp>

enum COORD {
  X,
  Y,
  Z
};

Camera::Camera() : m_fDistance(-5.0f), m_fAngleX(0.0f), m_fAngleY(0.0f), m_center(0.f, 0.f, 0.f), m_currentCamera(1), m_fMaxAngle(40) {
  computeDirectionVectors();
};

void Camera::initialization(const float &distance, const float &angleY, const glm::vec3 &eyesPosition, const float &maxAngle) {
  m_fDistance = distance;
  rotate(angleY);
  m_eyesPosition = eyesPosition;
  m_fMaxAngle = maxAngle;
}

void Camera::eventManager(const SDL_Event &e) {

  // Change the point of view
  if (e.type == SDL_KEYDOWN) {
    if (e.key.keysym.sym == SDLK_c) {
      if (m_currentCamera != 1)
        m_currentCamera = 1;
      else {
        m_currentCamera = 2;
        m_fTheta = glm::radians(m_fAngleX);
        m_fPhi = glm::radians(-m_fAngleY);
        computeDirectionVectors();
      }
    }
    if (e.key.keysym.sym == SDLK_v)
      m_currentCamera = 3;
  }

  // Handle the keys for the rotating camera
  if (m_currentCamera == 3) {
    switch (e.type) {
      case SDL_MOUSEMOTION:
        if (e.motion.xrel != 0)
          rotateRightThirdPerson(float(e.motion.xrel));
        if (e.motion.yrel != 0)
          rotateLeftThirdPerson(float(e.motion.yrel));
        break;

      default:
        break;
    }
  }//Handle the keys for the first person
  else if (m_currentCamera == 2) {
    switch (e.type) {

      case SDL_MOUSEMOTION:
        if (e.motion.xrel != 0) {
          rotateFrontFirstPerson(float(-e.motion.xrel) / 2.);
        }
        if (e.motion.yrel != 0) {
          rotateLeftFirstPerson(float(-e.motion.yrel) / 2.);
        }
        break;

      default:
        break;
    }
  }
}

void Camera::update(const glm::vec3 &center) {
  if (m_currentCamera == 2) {
    m_center = center + m_eyesPosition;
  } else {
    m_center = center;
  }
}

void Camera::rotate(const float &rotationY) {
  m_fAngleX = 10.f;
  m_fAngleY = -rotationY * (180. / M_PI);
  m_fPhi = m_fAngleY;
  m_fTheta = 0.f;
  computeDirectionVectors();
}

glm::mat4 Camera::getViewMatrix() const {
  if (m_currentCamera == 2 || m_currentCamera == 4) {
    return glm::lookAt(m_center, m_center + m_frontVector, m_upVector);
  } else {
    glm::mat4 VM = glm::mat4(1.f);
    VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, m_fDistance));
    VM = glm::rotate(VM, glm::radians(m_fAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    VM = glm::rotate(VM, glm::radians(m_fAngleY + 180.f), glm::vec3(0.0f, 1.0f, 0.0f));
    VM = glm::translate(VM, -m_center);
    if (m_currentCamera == 1) {
      VM = glm::translate(VM, glm::vec3(0.f, -1.f, 0.f));
    }
    return VM;
  }
}

// ========================== THIRD PERSON ========================

void Camera::moveForwardThirdPerson(const float &delta) {
  if (delta > 0 && m_fDistance >= -1.0f)
    return;
  m_fDistance += delta;
}

void Camera::rotateLeftThirdPerson(const float &degrees) {
  m_fAngleX += degrees;
}

void Camera::rotateRightThirdPerson(const float &degrees) {
  m_fAngleY += degrees;
}

// ========================== FIRST PERSON ========================

void Camera::moveForwardFirstPerson(const float &t) {
  m_center += t * m_frontVector;
  m_upVector = glm::cross(m_frontVector, m_leftVector);
}

void Camera::moveLeftFirstPerson(const float &t) {
  m_center += t * m_leftVector;
  m_upVector = glm::cross(m_frontVector, m_leftVector);
}

void Camera::rotateFrontFirstPerson(const float &degrees) {
  m_fPhi += glm::radians(degrees);
  if (m_currentCamera == 2) {
    m_fPhi = clamp(m_fPhi, glm::radians(-m_fAngleY - m_fMaxAngle), glm::radians(-m_fAngleY + m_fMaxAngle));
  }
  m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta) * std::cos(m_fPhi));

  m_leftVector = glm::vec3(std::sin(m_fPhi + M_PI / 2.), 0, std::cos(m_fPhi + M_PI / 2.));
}

void Camera::rotateLeftFirstPerson(const float &degrees) {
  m_fTheta += glm::radians(degrees);
  if (m_currentCamera == 2) {
    m_fTheta = clamp(m_fTheta, glm::radians(-m_fMaxAngle), glm::radians(m_fMaxAngle));
  }
  m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta) * std::cos(m_fPhi));

  m_leftVector = glm::vec3(std::sin(m_fPhi + M_PI / 2.), 0, std::cos(m_fPhi + M_PI / 2.));
}

void Camera::computeDirectionVectors() {
  m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta) * std::cos(m_fPhi));

  m_leftVector = glm::vec3(std::sin(m_fPhi + M_PI / 2.), 0, std::cos(m_fPhi + M_PI / 2.));

  m_upVector = glm::cross(m_frontVector, m_leftVector);
}