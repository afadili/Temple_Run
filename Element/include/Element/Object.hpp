/**
 * \file Object.hpp
 * \brief Declaration of the class "Object"
 */

#ifndef __OBJECT__HPP
#define __OBJECT__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include <Mesh/Mesh.hpp>

/**
 * \class Object
 * \brief Mother class of the objects on the map
 */
class Object {
protected:
  Mesh *m_mesh; /*!< Pointer on the mesh corresponding to the object */
  glm::vec3 m_position = glm::vec3(0, 0, 0); /*!< Position of the object in the world coordinates */
  glm::vec3 m_size = glm::vec3(1, 1, 1); /*!< Size of the object in the world coordinates */
  glm::vec3 m_rotation = glm::vec3(0, 0, 0); /*!< Rotation of the object in the world coordinates */

private:
  Object();

public:

  /**
   * \brief Constructor with mesh
   * \param mesh : pointer on the mesh corresponding to the object
   */
  Object(Mesh *mesh);


  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   */
  Object(Mesh *mesh, const glm::vec3 &position);

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   */
  Object(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size);

  /**
   * \brief Constructor with mesh and parameters
   * \param mesh : pointer on the mesh corresponding to the object
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates
   * \param rotation : rotation of the object in the world coordinates
   */
  Object(Mesh *mesh, const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation);

  /**
   * \brief Update object data. Function called at each drawing on ObjectList.
   */
  virtual
  void update(){};

  /**
   * \brief Translate the object
   * \param vec : translation vector
   * \return the new world coordinates matrix of the object
   */
  glm::mat4 translate(const glm::vec3 &vec);

  /**
   * \brief Rotate the object (in radian)
   * \param vec : rotation vector
   * \return the new world coordinates matrix of the object
   */
  glm::mat4 rotate(const glm::vec3 &vec);

  /**
   * \brief Scale the object
   * \param vec : scale vector
   * \return the new world coordinates matrix of the object
   */
  glm::mat4 scale(const glm::vec3 &vec);

  /**
   * \brief Get the world coordinates matrix of the object 
   * \return world coordinates matrix of the object 
   */
  glm::mat4 MWMatrix() const;

  /**
   * \brief Draw the object with is world coordinates, 
   * \param ProjMatrix : Projection matrix
   * \param ViewMatrix : view matrix of the camera, identity matrix by default
   * \param isBind : if the mesh has already been bind (default) or if it must be bind and debind in this function (false)
   */
  void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix = glm::mat4(), const bool isBind = true) const;

  /**
   * \brief Getter of mesh
   * \return m_mesh
   */
  inline
  Mesh *mesh() const {
    return m_mesh;
  }

  /**
   * \brief Opérateur << for print Object data
   */
  friend std::ostream &operator<<(std::ostream &os, const Object &obj) {
    // Print loaded shaders name
    os << "  -- Position = " << obj.m_position << "\n";
    os << "  -- Size = " << obj.m_size << "\n";
    os << "  -- Rotation = " << obj.m_rotation << "\n";
  }


};

#endif
