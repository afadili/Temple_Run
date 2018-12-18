/**
 * \file VBO.hpp
 * \brief description : Declaration of the class "VBO"
 */

#ifndef __VBO__HPP
#define __VBO__HPP

#include "Render/Render.hpp"

/**
 * \class VBO
 * \brief class defining a VBO and associated actions
 */

class VBO : public Render {
public:
  /**
   * \brief constructor
   */
  VBO();

  /**
   * \brief destructor
   */
  ~VBO();

  /**
   * \brief 
   */
  void bind();

  /**
   * \brief 
   */
  void debind();

  /**
   * \brief 
   * \param 
   */
  template <typename type>
  void fillBuffer(std::vector<type> &vect) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, vect.size() * sizeof (type), vect.data(), GL_STATIC_DRAW);
    debind();
  };

};

#endif