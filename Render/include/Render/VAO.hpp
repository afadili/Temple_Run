/**
 * \file VAO.hpp
 * \brief description : Declaration of the class "VAO"
 */

#ifndef __VAO__HPP
#define __VAO__HPP

#include "Render.hpp"
#include "VBO.hpp"
#include "IBO.hpp"

/**
 * \class VAO
 * \brief class defining a VAO and associated actions
 */

class VAO : public Render {
public:
  /**
   * \brief constructor
   */
  VAO();

  /**
   * \brief destructor
   */
  ~VAO();

  /**
   * \brief 
   */
  void bind() const;

  /**
   * \brief 
   */
  void debind() const;

  /**
   * \brief 
   * \param 
   */
  template <typename type>
  void fillBuffer(const std::vector<type> &vect,const VBO *vbo,const IBO *ibo = nullptr) {
    bind();

    if (ibo != nullptr)
      ibo->bind();

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    vbo->bind();

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof (type), (const GLvoid*) offsetof(type, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof (type), (const GLvoid*) offsetof(type, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof (type), (const GLvoid*) offsetof(type, texCoords));

    vbo->debind();

    debind();
  }

};

#endif