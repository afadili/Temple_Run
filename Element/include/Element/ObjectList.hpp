/**
 * \file ObjectList.hpp
 * \brief Declaration of the class "ObjectList"
 */

#ifndef __OBJECTLIST__HPP
#define __OBJECTLIST__HPP

#include <iostream>
#include <list>
#include <algorithm>

#include <GL/glew.h>
#include <GL/gl.h>

#include <Element/Object.hpp>

/**
 * \class ObjectList
 * \brief Management of a list of objects having a mesh (with a texture and a shader) in common
 */
class ObjectList {
protected:
  Mesh *m_mesh; /*!< Pointer on the mesh corresponding to all the object list */
  std::list<Object*> m_objects; /*!< List of all objects */

private:
  ObjectList();

public:

  /**
   * \brief Constructor with mesh
   * \param mesh : pointer on the mesh corresponding to all the object
   */
  ObjectList(Mesh *mesh);

  /**
   * \brief Constructor with the first element list 
   * \param obj : pointer on the obj element
   */
  ObjectList(Object *obj);

  /**
   * \brief Destructor: delete all objects and clear the list (don't delete the mesh)
   */
  ~ObjectList();

  /**
   * \brief Add an object to the list
   * \param obj : pointer on the obj element
   */
  inline
  void add(Object *obj) {
    m_objects.push_back(obj);
  }

  /**
   * \brief Create and add an object to the list
   * \param position : position of the object in the world coordinates
   * \param size : size of the object in the world coordinates, (1,1,1) by default
   * \param rotation : rotation of the object in the world coordinates, (0,0,0) by default
   */
  inline
  void add(const glm::vec3 &position, const glm::vec3 &size = glm::vec3(1, 1, 1), const glm::vec3 &rotation = glm::vec3(0, 0, 0)) {
    add(new Object(m_mesh, position, size, rotation));
  }

  /**
   * \brief Remove an object from the list
   * \param obj : pointer on the obj element
   * \param deleteIt : if the object must also be deleted from the memory (true by default)
   */
  void remove(Object *obj, const bool deleteIt = true);

  /**
   * \brief Draw all objects in the list
   * \param ProjMatrix : Projection matrix
   * \param ViewMatrix : view matrix of the camera, identity matrix by default
   */
  void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix = glm::mat4()) const;

  /**
   * \brief Getter of mesh
   * \return m_mesh
   */
  inline
  Mesh *mesh() const {
    return m_mesh;
  }

  /**
   * \brief Getter of the list
   * \return m_mesh
   */
  inline
  std::list<Object*> objects() const {
    return m_objects;
  }

};

#endif
