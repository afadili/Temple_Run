/**
 * \file Stone.hpp
 * \brief Declaration of the class "Stone"
 */

#ifndef __STONE__HPP
#define __STONE__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include "Object.hpp"

/**
 * \class Stone
 * \brief Mother class of all the different stones
 */
class Stone : public Object {
protected:
  float m_rotationSpeed = 0.05; /*!< speed of rotation of the stone per frame */

private:
  Stone();

public:

  /**
   * \brief Constructor with mesh
   * \param mesh : pointer on the mesh corresponding to the object
   */
  Stone(Mesh *mesh) : Object(mesh) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   */
  Stone(Mesh *mesh, const glm::vec3 &position) : Object(mesh, position) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   */
  Stone(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size) : Object(mesh, position, size) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   * \param rotation : rotation of the object in the world coordinates
   */
  Stone(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation) : Object(mesh, position, size, rotation) {
  };

  /**
   * \brief Update object data. Function called at each drawing on ObjectList.
   */
  void update();


};

#endif