#include <Element/ObjectList.hpp>

ObjectList::ObjectList(Mesh *mesh) : m_mesh(mesh) {
}

ObjectList::ObjectList(Object *obj) : m_mesh(obj->mesh()) {
  add(obj);
}

ObjectList::~ObjectList() {
  for (Object* elem : m_objects)
    delete elem;
  m_objects.clear();
}

void ObjectList::remove(Object *obj, const bool deleteIt) {
  m_objects.remove(obj);
  if (deleteIt)
    delete obj;
}

void ObjectList::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix) const {
  // bind the mesh 
  m_mesh->bind();

  // Mesh instances
  for (Object* obj : m_objects) {
      obj->update();
      m_mesh->draw(ProjMatrix, obj->MWMatrix(), ViewMatrix);
  }

  // debind the mesh 
  m_mesh->debind();
}