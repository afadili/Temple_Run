/**
 * \file Skybox.hpp
 * \brief Declaration of the class "Skybox"
 */

#ifndef __SKYBOX__HPP
#define __SKYBOX__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include "Object.hpp"

/**
 * \class Skybox
 * \brief Class of the blocs on the corner
 */
class Skybox : public Object {
protected:

private:
  Skybox();

public:

  /**
   * \brief Constructor with mesh
   * \param mesh : pointer on the mesh corresponding to the object
   */
  Skybox(Mesh *mesh) : Object(mesh) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   */
  Skybox(Mesh *mesh, const glm::vec3 &position) : Object(mesh, position) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   */
  Skybox(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size) : Object(mesh, position, size) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   * \param rotation : rotation of the object in the world coordinates
   */
  Skybox(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation) : Object(mesh, position, size, rotation) {
  };

  /**
   * \brief Getter of type
   * \return the type
   */
  inline
  std::string type() const override {
    return "Skybox";
  }


};

#endif