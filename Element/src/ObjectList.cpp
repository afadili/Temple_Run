#include <Element/ObjectList.hpp>

ObjectList::ObjectList(Mesh *mesh) : m_mesh(mesh) {
}

ObjectList::ObjectList(Object *obj) : m_mesh(obj->mesh()) {
  add(obj);
}

ObjectList::~ObjectList() {
  for (auto&& elem : m_objects)
    delete elem;
  m_objects.clear();
}

void ObjectList::remove(Object *obj, const bool deleteIt) {
  m_objects.remove(obj);
  if (deleteIt)
    delete obj;
}

/**
 * \brief Draw all objects in the list
 * \param ProjMatrix : Projection matrix
 * \param ViewMatrix : view matrix of the camera, identity matrix by default
 */
void ObjectList::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix) const {
  // bind the mesh 
  m_mesh->bind();

  // Mesh instances
  for (auto&& obj : m_objects)
    m_mesh->draw(ProjMatrix, obj->MWMatrix(), ViewMatrix);

  // debind the mesh 
  m_mesh->debind();
}