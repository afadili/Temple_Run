/**
 * \file:  Mesh.hpp
 * \brief Description: Decalaration of the class "Mesh"
 */

#ifndef __MESH__HPP
#define __MESH__HPP

#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <string>
#include <fstream>

#include <glimac/Shader.hpp>
#include <glimac/common.hpp>

#include <Render/VAO.hpp>
#include <Render/VBO.hpp>
#include <Render/IBO.hpp>
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>

class Mesh {
protected:
  std::vector<ShapeVertex> m_vertices; /*!< Vector with the vertices */
  std::vector<int> m_indexVer; /*!< Vector with the index of the vertices */
  ShaderManager *m_shader; /*!< Shader of the Mesh */
  Texture *m_texture; /*!< Texture of the mesh */
  GLsizei m_nbVertex; /*!< Number of Vertex of the Mesh */
  VBO *m_vbo = new VBO(); /*!<  Pointer on VBO manager */
  VAO *m_vao = new VAO(); /*!<  Pointer on VAO manager */
  IBO *m_ibo = new IBO(); /*!<  Pointer on IBO manager */
  GLsizei s_nbMesh; /*!< Number of Meshs */

private:
  Mesh() = default;

public:

  /**
   * \brief constructor of Mesh using a vector of ShapeVertex
   * \param vertices : vector of ShapeVertex
   */
  Mesh(const std::vector<ShapeVertex> &vertices);

  /**
   * \brief constructor of Mesh using a vector of ShapeVertex
   * \param vertices : vector of all the vertices
   * \param indexVer : vector of the index of the vertices
   */
  Mesh(const std::vector<ShapeVertex> &vertices, const std::vector<int> &indexVer);

  /**
   * \brief constructor of Mesh using a vector of ShapeVertex
   * \param vertices : vector of all the vertices
   * \param shader : shader of the mesh
   * \param textures : texture of the mesh
   */
  Mesh(const std::vector<ShapeVertex> &vertices, ShaderManager *shader, Texture *texture);


  /**
   * \brief constructor of Mesh using a vector of ShapeVertex
   * \param vertices : vector of all the vertices
   * \param shader : shader of the mesh
   * \param textures : texture of the mesh
   */
  Mesh(ShaderManager *shader, Texture *texture);

  /**
   * \brief constructor of Mesh using a vector of ShapeVertex
   * \param vertices : vector of all the vertices
   * \param indexVer : vector of the index of the vertices
   * \param shader : shader of the mesh
   * \param textures : texture of the mesh
   */
  Mesh(const std::vector<ShapeVertex> &vertices, const std::vector<int> &indexVer, ShaderManager *shader, Texture *texture);

  /**
   * \brief destructor of Mesh
   */
  ~Mesh();

  /**
   * \brief getter of the pointer that leads us to the shapeVertex
   * \return : the pointer that leads us to the vector of vertices
   */
  inline
  const ShapeVertex* dataPointer() const {
    return &m_vertices[0];
  }

  /**
   * \brief getter of the number of Vertex of the Mesh
   * \return : the number of Vertex of the Mesh
   */
  GLsizei vertexCount() const {
    return m_nbVertex;
  }

  /**
   * \brief fillBuffer of the vao, vbo and ibo
   */
  void fillBuffers();

  inline
  std::vector<ShapeVertex> vertices() const {
    return m_vertices;
  }

  inline
  std::vector<int> indexVer() const {
    return m_indexVer;
  }

  inline
  VBO *vbo() const {
    return m_vbo;
  }

  inline
  VAO *vao() const {
    return m_vao;
  }

  inline
  IBO *ibo() const {
    return m_ibo;
  }

  inline
  ShaderManager *shader() const {
    return m_shader;
  }

  inline
  Texture *texture() const {
    return m_texture;
  }

  inline
  bool haveIBO() const {
    return m_indexVer.size() > 0 ? true : false;
  }

  /**
   * \brief Opérateur << for print a mesh data
   */
  friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh) {
    // Print position
    os << "-- Vertices position (" << mesh.vertices().size() << ") = {\n";
    for (auto vertex : mesh.vertices())
      os << vertex.position << "\n";
    os << "}\n";

    // Print index
    os << "-- Vertices index (" << mesh.indexVer().size() << ") = [ ";
    for (auto index : mesh.indexVer())
      os << index << " ";
    os << "]\n";
    return os;
  }
};



#endif