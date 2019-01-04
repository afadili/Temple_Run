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
#include <glimac/FilePath.hpp>

#include <Error/DevError.hpp>
#include <Error/Error.hpp>

#include <Render/VAO.hpp>
#include <Render/VBO.hpp>
#include <Render/IBO.hpp>
#include <Render/ShaderManager.hpp>
#include <Render/Texture.hpp>

class Mesh {
protected:
  std::string m_name; /*!< Named of the mesh */
  std::vector<ShapeVertex> m_vertices; /*!< Vector with the vertices */
  std::vector<int> m_indexVer; /*!< Vector with the index of the vertices */
  ShaderManager *m_shader; /*!< Shader of the Mesh */
  Texture *m_texture; /*!< Texture of the mesh */
  GLsizei m_nbVertex; /*!< Number of Vertex of the Mesh */
  VBO *m_vbo = new VBO(); /*!<  Pointer on VBO manager */
  VAO *m_vao = new VAO(); /*!<  Pointer on VAO manager */
  IBO *m_ibo = new IBO(); /*!<  Pointer on IBO manager */
  GLsizei s_nbMesh; /*!< Number of Meshs */

public:
  Mesh() = default;

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
   * \brief constructor of Mesh using an object file
   * \param objPath : the file of the object data (.obj)
   */
  Mesh(const glimac::FilePath &objPath);

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
  inline
  GLsizei vertexCount() const {
    return m_nbVertex;
  }

  /**
   * \brief fillBuffer of the vao, vbo and ibo
   */
  void fillBuffers();

  /**
   * \brief bind the vao, the shader and the texture of the mesh for draw it 
   */
  void bind() const;

  /**
   * \brief debind the vao and the texture of the mesh
   */
  void debind() const;

  /**
   * \brief Draw the mesh, the mesh must be bind and uniform variables should be sent before
   */
  void draw() const;

  /**
   * \brief Draw the mesh with the uniform variables in parameter, the mesh must be bind before and unbind after
   * \param ProjMatrix : Projection matrix
   * \param MWMatrix : world coordinates matrix of the model, also used for normal matrix (normalMatrix = inverse(MWMatrix))
   * \param ViewMatrix : view matrix of the camera, identity matrix by default
   */
  void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MWMatrix, const glm::mat4 &ViewMatrix = glm::mat4()) const;

  /**
   * \brief Load object file and get is vertices, textures and normals data, created with http://www.opengl-tutorial.org/fr/beginners-tutorials/tutorial-7-model-loading/
   * \param objPath : the file of the object data (.obj)
   */
  void loadObj(const glimac::FilePath &objPath);

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
   * \brief Getter of name
   * \return m_name
   */
  inline
  const std::string &name() const {
    return m_name;
  }

  /**
   * \brief Setter of name
   * \return m_name
   */
  inline
  std::string &name() {
    return m_name;
  }

  /**
   * \brief Opérateur << for print a mesh data
   */
  friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh) {
    // Print shader
    if (mesh.m_shader)
      os << "-- Shader = {\n" << *mesh.m_shader << "}\n";
    else
      os << "-- Shader = NaN\n";

    // Print texture
    if (mesh.m_texture)
      os << "-- Texture = {\n" << *mesh.m_texture << "}\n";
    else
      os << "-- Texture = NaN\n";

    // Print position
    os << "-- Vertices position (" << mesh.vertices().size() << ") = {\n";
    for (const ShapeVertex &vertex : mesh.vertices())
      os << "  " << vertex.position << "\n";
    os << "}\n";

    // Print index
    os << "-- Vertices index (" << mesh.indexVer().size() << ") = [ ";
    for (const int &index : mesh.indexVer())
      os << index << " ";
    os << "]\n";

    // Print normal
    os << "-- Normals position (" << mesh.vertices().size() << ") = {\n";
    for (const ShapeVertex &vertex : mesh.vertices())
      os << "  " << vertex.normal << "\n";
    os << "}\n";

    // Print texture
    os << "-- Texture position (" << mesh.vertices().size() << ") = {\n";
    for (const ShapeVertex &vertex : mesh.vertices())
      os << "  " << vertex.texCoords << "\n";
    os << "}\n";

    return os;
  }
};



#endif