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
  if (m_direction.x != 0.f)
    rotation = m_direction.x * M_PI / 2.;
  else
    rotation = (m_direction.z - 1) * M_PI / 2.;
  std::cout << rotation << std::endl;
  m_rotation = glm::vec3(0.f, rotation, 0.f);
}

void Character::moveLeft() {
  m_position = absolutePosition(glm::vec3(1.f, 0.f, 0.f));
  roundPosition();
}

void Character::moveRight() {
  m_position = absolutePosition(glm::vec3(-1.f, 0.f, 0.f));
  roundPosition();
}

void Character::turnLeft() {
  if (m_direction.x != 0.f)
    direction(glm::vec3(0.f, 0.f, -m_direction.x));
  else
    direction(glm::vec3(m_direction.z, 0.f, 0.f));
  roundPosition();
}

void Character::turnRight() {
  if (m_direction.x != 0)
    direction(glm::vec3(0.f, 0.f, m_direction.x));
  else
    direction(glm::vec3(-m_direction.z, 0.f, 0.f));
  roundPosition();
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
