#include <Element/Character.hpp>

void Character::update() {
  lastUpdate();

  // automatic translation by speed
 // translate(m_direction * m_speed * lastUpdate());

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

void Character::jump() {
  if (!m_isJumping)
    std::abs(m_jumpSpeed);
  m_isJumping = true;
}