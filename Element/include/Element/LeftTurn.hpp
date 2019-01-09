/**
 * \file LeftTurn.hpp
 * \brief Declaration of the class "LeftTurn"
 */

#ifndef __LEFTTURN__HPP
#define __LEFTTURN__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include "Object.hpp"

/**
 * \class LeftTurn
 * \brief Class of the blocs on the corner
 */
class LeftTurn : public Object {
protected:

private:
  LeftTurn();

public:

  /**
   * \brief Constructor with mesh
   * \param mesh : pointer on the mesh corresponding to the object
   */
  LeftTurn(Mesh *mesh) : Object(mesh) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   */
  LeftTurn(Mesh *mesh, const glm::vec3 &position) : Object(mesh, position) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   */
  LeftTurn(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size) : Object(mesh, position, size) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   * \param rotation : rotation of the object in the world coordinates
   */
  LeftTurn(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation) : Object(mesh, position, size, rotation) {
  };

  /**
   * \brief Getter of type
   * \return the type
   */
  inline
  std::string type() const override {
    return "LeftTurn";
  }


};

#endif