/**
 * \file Character.hpp
 * \brief Declaration of the class "Character"
 */

#ifndef __CHARACTER__HPP
#define __CHARACTER__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include "Object.hpp"

/**
 * \class Character
 * \brief Mother class of the different characters
 */
class Character : public Object {
protected:
  int m_life; /*!< life of the character */
  float m_speed; /*!< speed of the character */

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

};

#endif