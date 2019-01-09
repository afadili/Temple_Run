/**
 * \file Object.hpp
 * \brief Declaration of the class "Object"
 */

#ifndef __OBJECT__HPP
#define __OBJECT__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <ctime>

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
  std::clock_t m_lastUpdate = 0; /*!< Date of last update of the object */

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
  void update() {
    m_lastUpdate = std::clock();
  };

  /**
   * \brief Translate the object
   * \param vec : translation vector
   */
  inline
  void translate(const glm::vec3 &vec) {
    m_position += vec;
  }

  /**
   * \brief Rotate the object (in radian)
   * \param vec : rotation vector
   */
  inline
  void rotate(const glm::vec3 &vec) {
    m_rotation += vec;
  }

  /**
   * \brief Scale the object
   * \param vec : scale vector
   */
  inline
  void scale(const glm::vec3 &vec) {
    m_size += vec;
  }

  /**
   * \brief Get the world coordinates matrix of the object 
   * \return world coordinates matrix of the object 
   */
  virtual
  glm::mat4 MWMatrix() const;


  /**
   * \brief Get the world position matrix of the object 
   * \return world position matrix of the object 
   */
  glm::mat4 positionMatrix() const;

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
   * \brief Getter of type
   * \return the type
   */
  inline
  virtual std::string type() const {
    return "Object";
  }

  /**
   * \brief Getter of grid position
   * \return position of the object on a grid (integer values)
   */
  const std::vector<int> gridPosition() const;

  /**
   * \brief Getter of grid position with a displacement according to the rotation of the object
   * \param x : the x displacement related to the object
   * \param y : the y displacement related to the object
   * \param z : the z displacement related to the object
   * \return position of the object on a grid (integer values) with the displacement
   */
  const std::vector<int> gridPosition(const int x, const int y, const int z) const;

  /**
   * \brief Getter of the absolute position with a displacement according to the rotation of the object
   * \return absolute position of the object with the displacement
   */
  glm::vec3 absolutePosition(const glm::vec3 &vec = glm::vec3(0, 0, 0)) const;

  /**
   * \brief Round the actual position to center the object on the box of the current grid
   * \param x : if we do the rounding on the x axis
   * \param y : if we do the rounding on the y axis
   * \param z : if we do the rounding on the z axis
   */
  void roundPosition(bool onX = true, bool onY = false, bool onZ = true);

  /**
   * \brief Getter of position
   * \return m_position
   */
  inline
  const glm::vec3 &position() const {
    return m_position;
  }

  /**
   * \brief Setter of position
   * \return m_position
   */
  inline
  glm::vec3 &position() {
    return m_position;
  }

  /**
   * \brief Getter of size
   * \return m_size
   */
  inline
  const glm::vec3 &size() const {
    return m_size;
  }

  /**
   * \brief Setter of size
   * \return m_size
   */
  inline
  glm::vec3 &size() {
    return m_size;
  }

  /**
   * \brief Getter of rotation
   * \return m_rotation
   */
  inline
  const glm::vec3 &rotation() const {
    return m_rotation;
  }

  /**
   * \brief Setter of rotation
   * \return m_rotation
   */
  inline
  glm::vec3 &rotation() {
    return m_rotation;
  }

  /**
   * \brief Get the elapsed time since the last update
   * \return the elapsed time in secondes
   */
  float lastUpdate() const;

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
