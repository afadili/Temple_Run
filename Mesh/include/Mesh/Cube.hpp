/**
 * \file:  Cube.hpp
 * \brief Decalaration of the class "Cube"
 */

#ifndef __CUBE__HPP
#define __CUBE__HPP

#include "Mesh.hpp"

class Cube : public Mesh {
protected:



public:
  /**
   * \brief constructor of Cube
   */
  Cube();

  /**
   * \brief constructor of Cube
   * \param shader : shader of the cube
   * \param textures : texture of the cube
   */
  Cube(ShaderManager *shader, Texture *texture);

  /**
   * \brief constructor of Cube
   * \param width : size of the cube
   * \param shader : shader of the cube
   * \param textures : texture of the cube 
   */
  Cube(const glm::vec3 &width, ShaderManager *shader, Texture *texture);

  /**
   * \brief constructor of Cube
   * \param width : size of the cube
   */
  Cube(const glm::vec3 &width);

  /**
   * \brief destructor of Cube
   */
  ~Cube() = default;


  /**
   * \brief generates the vertices of the cube
   * \param width : size of the cube
   */
  void generateVertices(const glm::vec3 &width);

  /**
   * \brief generates the index with the vertices of the cube
   */
  void generateIndexs();
};

#endif