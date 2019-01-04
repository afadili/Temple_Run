/**
 * \file Character.hpp
 * \brief Declaration of the class "Character"
 */

#ifndef __CHARACTER__HPP
#define __CHARACTER__HPP

#include "Object.hpp"

/**
 * \class Character
 * \brief Mother class of the different characters
 */
class Character : public Object {
protected:
  glm::vec3 m_direction = glm::vec3(1, 0, 0); /*!< the direction vector of the character */
  float m_speed = 3; /*!< speed of the character, blocks by seconds */
  float m_jumpSpeed = 0.75; /*!< speed of the jumping animation, blocks by seconds */
  float m_maxJump = 1.3; /*!< maximum jump height */
  float m_turnVelocity = 0; /*!< velocity on turn */
  float m_translateVelocity = 0; /*!< velocity on translate */
  float m_jumpVelocity = 0; /*!< velocity on jump */
  float m_jumpState = 0; /*!< distance course by the jump */
  float m_friction = 0.98; /*!< the friction for all animation */
  bool m_isJumping = false; /*!< if the character is jumping */

private:
  Character();

public:

  /**
   * \brief Constructor with mesh
   * \param mesh : pointer on the mesh corresponding to the object
   */
  Character(Mesh *mesh) : Object(mesh) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   */
  Character(Mesh *mesh, const glm::vec3 &position) : Object(mesh, position) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   */
  Character(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size) : Object(mesh, position, size) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   * \param rotation : rotation of the object in the world coordinates
   */
  Character(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation) : Object(mesh, position, size, rotation) {
  };

  /**
   * \brief getter for speed
   * \return m_speed
   */
  inline
  const float &speed() const {
    return m_speed;
  }

  /**
   * \brief setter for speed
   * \return m_speed
   */
  inline
  float &speed() {
    return m_speed;
  }

  /**
   * \brief getter for jump speed
   * \return m_jumpSpeed
   */
  inline
  const float &jumpSpeed() const {
    return m_jumpSpeed;
  }

  /**
   * \brief setter for jump speed
   * \return m_jumpSpeed
   */
  inline
  float &jumpSpeed() {
    return m_jumpSpeed;
  }

  /**
   * \brief getter for max jump
   * \return m_maxJump
   */
  inline
  const float &maxJump() const {
    return m_speed;
  }

  /**
   * \brief setter for max jump
   * \return m_maxJump
   */
  inline
  float &maxJump() {
    return m_maxJump;
  }

  /**
   * \brief change the direction of the character and his orientation
   */
  void direction(const glm::vec3 &direction);


  /**
   * \brief Update object data. Function called at each drawing on ObjectList.
   */
  void update();

  /**
   * \brief Launch a translation animation to the left
   */
  void moveLeft();

  /**
   * \brief Launch a translation animation to the right
   */
  void moveRight();

  /**
   * \brief Launch a rotation animation to the left
   */
  void turnLeft();

  /**
   * \brief Launch a rotation animation to the right
   */
  void turnRight();

  /**
   * \brief Launch a jump animation
   */

  void jump();

};

#endif