#include <Game/Camera.hpp>

const double PI = 3.141592653589;
const double HALF_PI = PI / 2;
const float Camera::VIEW_WIDTH = 30.f;
static const bool DEBUG = true;

enum COORD
{
  X,
  Y,
  Z
};

Camera::Camera() : m_fDistance(-15.0f), m_fAngleX(0.0f), m_fAngleY(0.0f), m_center(0.f, 0.f, 0.f), m_currentCamera(1) {
  computeDirectionVectors();
};

void Camera::eventManager(const SDL_Event &e){

  // Change the point of view
  if (e.type == SDL_KEYDOWN){
    if (e.key.keysym.sym == SDLK_c){
      if (m_currentCamera != 1)
        m_currentCamera = 1;
      else{
        m_currentCamera = 2;
        m_fTheta = glm::radians(m_fAngleX);
        m_fPhi = glm::radians(-m_fAngleY);
        computeDirectionVectors();
      }
    }
    if (e.key.keysym.sym == SDLK_v && DEBUG)
      m_currentCamera = 3;
    if (e.key.keysym.sym == SDLK_b && DEBUG)
      m_currentCamera = 4;
    std::cout << "Changement de camera : " << m_currentCamera << std::endl;
  }

  // Handle the keys for the rotating camera
  if (m_currentCamera == 3){
    switch (e.type){
    /* Touche clavier */
    case SDL_KEYDOWN:
    {
      float zoom = 1.0f;
      if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP){
        //std::cout << "Z or UP pressed" << std::endl;
        moveForwardThirdPerson(zoom);
      }
      else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN){
        //std::cout << "S or DOWN pressed" << std::endl;
        moveForwardThirdPerson(-zoom);
      }
    }
    break;

    case SDL_MOUSEMOTION:
    {
      float speed = 1.f;
      if (e.motion.xrel != 0){
        rotateRightThirdPerson(float(e.motion.xrel) * speed);
      }
      if (e.motion.yrel != 0){
        rotateLeftThirdPerson(float(e.motion.yrel) * speed);
      }
    }
    break;

    default:
      break;
    }
  }

  //Handle the keys for the first person
  else if (m_currentCamera == 2 || m_currentCamera == 4){
    switch (e.type){
    /* Touche clavier DOWN */
    case SDL_KEYDOWN:
    {
      if (m_currentCamera == 4){
        if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP){
          KEY_UP_PRESSED = true;
        }
        if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN){
          KEY_DOWN_PRESSED = true;
        }
        if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_LEFT){
          KEY_LEFT_PRESSED = true;
        }
        if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT){
          KEY_RIGHT_PRESSED = true;
        }
      }
    }
    break;

    case SDL_KEYUP:
    {
      if (m_currentCamera == 4){
        if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP){
          KEY_UP_PRESSED = false;
        }
        if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN){
          KEY_DOWN_PRESSED = false;
        }
        if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_LEFT){
          KEY_LEFT_PRESSED = false;
        }
        if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT){
          KEY_RIGHT_PRESSED = false;
        }
      }
    }
    break;

    case SDL_MOUSEMOTION:
    {
      float speed = 0.5f;
      std::cout << "Mouse move: ";
      std::cout << e.motion.xrel << " | " << e.motion.yrel << " | Phi: " << m_fPhi << " | Theta: " << m_fTheta << std::endl;
      if (e.motion.xrel != 0)
      {
        rotateFrontFirstPerson(float(-e.motion.xrel) * speed);
      }
      if (e.motion.yrel != 0)
      {
        rotateLeftFirstPerson(float(e.motion.yrel) * speed);
      }
    }
    break;

    default:
      break;
    }
  }
}


void Camera::update(const glm::vec3 &center){
  /* CONTROL */
  if (m_currentCamera == 4){
    float speed = 0.1f;
    if (KEY_UP_PRESSED){
      moveForwardFirstPerson(speed);
    }
    else if (KEY_DOWN_PRESSED){
      moveForwardFirstPerson(-speed);
    }
    else if (KEY_LEFT_PRESSED){
      KEY_LEFT_PRESSED = true;
      moveLeftFirstPerson(speed);
    }
    else if (KEY_RIGHT_PRESSED){
      KEY_RIGHT_PRESSED = true;
      moveLeftFirstPerson(-speed);
    }
  }
  else if (m_currentCamera == 2){
    m_center = center + glm::vec3(0.f, 1.f, 0.f);
  }
  else {
    m_center = center;
  }
}

void Camera::characterIntel(const float &scale, const glm::vec3 &angles){
  m_fDistance = scale * -10.0f;
  m_fAngleX = 10.f;
  m_fAngleY = -angles[Y];
  m_fPhi = glm::radians(m_fAngleY);
  m_fTheta = 0.f;
  computeDirectionVectors();
}

glm::mat4 Camera::getViewMatrix() const{
  if (m_currentCamera == 2 || m_currentCamera == 4){
    return glm::lookAt(m_center, m_center + m_frontVector, m_upVector);
  }
  else{
    glm::mat4 VM = glm::mat4(1.f);
    VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, m_fDistance));
    VM = glm::rotate(VM, glm::radians(m_fAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    VM = glm::rotate(VM, glm::radians(m_fAngleY + 180.f), glm::vec3(0.0f, 1.0f, 0.0f));
    VM = glm::translate(VM, -m_center);
    if (m_currentCamera == 1){
      VM = glm::translate(VM, glm::vec3(0.f, -1.f, 0.f));
    }
    return VM;
  }
}

// ========================== THIRD PERSON ========================
void Camera::moveForwardThirdPerson(const float &delta){
  if (delta > 0 && m_fDistance >= -1.0f)
    return;
  m_fDistance += delta;
}

void Camera::rotateLeftThirdPerson(const float &degrees){
  m_fAngleX += degrees;
}

void Camera::rotateRightThirdPerson(const float &degrees){
  m_fAngleY += degrees;
}

// ========================== FIRST PERSON ========================
void Camera::moveForwardFirstPerson(const float &t){
  m_center += t * m_frontVector;
  m_upVector = glm::cross(m_frontVector, m_leftVector);
}

void Camera::moveLeftFirstPerson(const float &t){
  m_center += t * m_leftVector;
  m_upVector = glm::cross(m_frontVector, m_leftVector);
}

void Camera::rotateFrontFirstPerson(const float &degrees){
  m_fPhi += glm::radians(degrees);
  if (m_currentCamera == 2){
    m_fPhi = clamp(m_fPhi, glm::radians(-m_fAngleY - Camera::VIEW_WIDTH), glm::radians(-m_fAngleY + Camera::VIEW_WIDTH));
  }
  m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta) * std::cos(m_fPhi));

  m_leftVector = glm::vec3(std::sin(m_fPhi + HALF_PI), 0, std::cos(m_fPhi + HALF_PI));
}

void Camera::rotateLeftFirstPerson(const float &degrees){
  m_fTheta += glm::radians(degrees);
  if (m_currentCamera == 2){
    m_fTheta = clamp(m_fTheta, glm::radians(-Camera::VIEW_WIDTH), glm::radians(Camera::VIEW_WIDTH));
  }
  m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta) * std::cos(m_fPhi));

  m_leftVector = glm::vec3(std::sin(m_fPhi + HALF_PI), 0, std::cos(m_fPhi + HALF_PI));
}

void Camera::computeDirectionVectors(){
  m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta) * std::cos(m_fPhi));

  m_leftVector = glm::vec3(std::sin(m_fPhi + HALF_PI), 0, std::cos(m_fPhi + HALF_PI));

  m_upVector = glm::cross(m_frontVector, m_leftVector);
}