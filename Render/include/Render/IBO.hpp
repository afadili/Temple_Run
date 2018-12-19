/**
 * \file IBO.hpp
 * \brief description : Declaration of the class "IBO"
 */

#ifndef __IBO__HPP
#define __IBO__HPP

#include "Render.hpp"

/**
 * \class IBO
 * \brief class defining a IBO and associated actions
 */

class IBO : public Render {
public:
  /**
   * \brief constructor
   */
  IBO();

  /**
   * \brief destructor
   */
  ~IBO();

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
  void fillBuffer(const std::vector<type> &vect) {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vect.size() * sizeof(type), vect.data(), GL_STATIC_DRAW);
    debind();
  };

};

#endif