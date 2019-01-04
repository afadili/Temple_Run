/**
 * \file FinishingLine.hpp
 * \brief Declaration of the class "FinishingLine"
 */

#ifndef __FINISHINGLINE__HPP
#define __FINISHINGLINE__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include "Object.hpp"

/**
 * \class FinishingLine
 * \brief class of the finishing line
 */
class FinishingLine : public Stone {
protected:

private:
  FinishingLine();

public:

  /**
   * \brief Constructor with mesh
   * \param mesh : pointer on the mesh corresponding to the object
   */
  FinishingLine(Mesh *mesh) : Stone(mesh) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   */
  FinishingLine(Mesh *mesh, const glm::vec3 &position) : Stone(mesh, position) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   */
  FinishingLine(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size) : Stone(mesh, position, size) {
  };

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   * \param rotation : rotation of the object in the world coordinates
   */
  FinishingLine(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation) : Stone(mesh, position, size, rotation) {
  };

  /**
   * \brief Getter of type
   * \return the type
   */
  inline
  std::string type() const override {
    return "FinishingLine";
  }
};

#endif