/**
 * \file Cube.hpp
 * \brief Decalaration of the class "Cube"
 */

#ifndef __CUBE__HPP
#define __CUBE__HPP

#include "Mesh.hpp"

/**
 * \class Cube
 * \brief create a cube-shaped mesh
 */
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
   * \param size : size of the cube in x, y and z
   * \param shader : shader of the cube
   * \param textures : texture of the cube 
   */
  Cube(const glm::vec3 &size, ShaderManager *shader, Texture *texture);

  /**
   * \brief constructor of Cube
   * \param size : size of the cube in x, y and z
   */
  Cube(const glm::vec3 &size);

  /**
   * \brief destructor of Cube
   */
  ~Cube() = default;


  /**
   * \brief generates the vertices of the cube
   * \param size : size of the cube in x, y and z
   */
  void generateVertices(const glm::vec3 &size);

  /**
   * \brief generates the index with the vertices of the cube
   */
  void generateIndexs();
};

#endif