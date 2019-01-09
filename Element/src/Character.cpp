#include <Element/Character.hpp>

void Character::update() {

  // jump
  if (m_isJumping) {
    // if we are at the top, we reverse the speed
    if (m_jumpState >= m_maxJump) {
      m_jumpSpeed = -m_jumpSpeed;
      m_jumpVelocity = 0;
    }

    m_jumpVelocity += m_jumpSpeed * lastUpdate();
    m_jumpState += m_jumpVelocity * m_friction;
    m_position.y += m_jumpVelocity * m_friction;

    // if the jump is over
    if (m_jumpState <= 0) {
      m_position.y = 0;
      m_isJumping = false;
    }
  }


  Object::update();
}

void Character::direction(const glm::vec3 &direction) {
  m_direction = direction;
  float rotation;
  if (direction.x != 0)
    rotation = direction.x * M_PI / 2.;
  else
    rotation = (direction.z - 1) * M_PI / 2.;

  rotate(glm::vec3(0, rotation, 0));
}

void Character::moveLeft() {
  translate(glm::vec3(1.f, 0.f, 0.f));
}

void Character::moveRight() {
  translate(glm::vec3(-1.f, 0.f, 0.f));
}

void Character::turnLeft() {
  
}

void Character::turnRight() {

}

void Character::jump() {
  /*if (!m_isJumping)
    std::abs(m_jumpSpeed);
  m_isJumping = true;*/
  translate(glm::vec3(0.f, 0.f, 0.f));
}

void Character::run() {
  translate(m_direction * m_speed);
}
