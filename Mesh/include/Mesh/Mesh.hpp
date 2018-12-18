/**
* \file:  Mesh.hpp
* \brief Description: Decalaration of the class "Mesh"
*/

#ifndef __MESH__HPP
#define __MESH__HPP

#include <iostream>
#include <Render/Texture.hpp>
#include <glimac/Shader.hpp>
#include <glimac/common.hpp>
#include <Render/VAO.hpp>
#include <Render/VBO.hpp>
#include <Render/IBO.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>


class Mesh {

protected:
	std::vector<ShapeVertex> m_vertices;   /*!< Vector with the vertices */
	std::vector<uint32_t> m_indexVer;	/*!< Vector with the index of the vertices */
	Shader *m_shader;   /*!< Shader of the Mesh */
	Texture *m_texture;   /*!< Texture of the mesh */
	GLsizei m_nbVertex;   /*!< Number of Vertex of the Mesh */
	VBO m_vbo;   /*!<  Identifiant of the VBO*/
	VAO m_vao;   /*!<  Identifiant of the VAO */
	IBO m_ibo;   /*!<  Identifiant of the IBO */
	GLsizei s_nbMesh;   /*!< Number of Meshs */

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
	Mesh(const std::vector<ShapeVertex> &vertices, const std::vector<uint32_t> &indexVer);

	/**
	* \brief constructor of Mesh using a vector of ShapeVertex
    * \param vertices : vector of all the vertices
    * \param shader :
    * \param textures : 
	*/
	Mesh(const std::vector<ShapeVertex> &vertices, Shader *shader, Texture *texture);


	/**
	* \brief constructor of Mesh using a vector of ShapeVertex
    * \param vertices : vector of all the vertices
    * \param shader :
    * \param textures : 
	*/
	Mesh(Shader *shader, Texture *texture);

	/**
	* \brief constructor of Mesh using a vector of ShapeVertex
    * \param vertices : vector of all the vertices
    * \param indexVer : vector of the index of the vertices
    * \param shader :
    * \param textures :
	*/
	Mesh(const std::vector<ShapeVertex> &vertices, const std::vector<uint32_t> &indexVer, Shader *shader, Texture *texture);

	/**
	* \brief destructor of Mesh
	*/	
	~Mesh();


	/**
	* \brief getter of the pointer that leads us to the shapeVertex
    * \return : the pointer that leads us to the vector of vertices
	*/
	const ShapeVertex* getDataPointer() const {
        return &m_vertices[0];
    }

	/**
	* \brief getter of the number of Vertex of the Mesh
    * \return : the number of Vertex of the Mesh
	*/
	GLsizei getVertexCount() const {
        return m_nbVertex;
    }

	/**
	* \brief fillBuffer of the vao, vbo and ibo
	*/	
	void fillBuffers();
	
};

#endif