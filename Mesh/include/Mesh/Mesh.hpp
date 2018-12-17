/**
* \file:  Mesh.hpp
* \brief Description: Decalaration of the class "Mesh"
*/

#ifndef __MESH__HPP
#define __MESH__HPP

#include <iostream>
#include <Render/Texture.hpp>
#include <Render/Shader.hpp>
#include <Render/VAO.hpp>
#include <Render/VBO.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>


class Mesh {
protected : 
	std::string m_name;    /*!< name of the Mesh */
	std::vector<Texture> m_textures;   /*!< Vector with textures */
	//Shader m_shader;   /*!< Shader of the Mesh */
	//std::vector<ShapeVertex> m_vertices;   /*!< Vector with ShapeVertex */
	GLsizei m_nbVertex;   /*!< Number of Vertex of the Mesh */
	VBO m_vbo;   /*!<  Identifiant of the VBO*/
	VAO m_vao;   /*!<  Identifiant of the VAO */
	GLsizei s_nbMesh;   /*!< Number of Meshs */

public:
	/**
	* \brief constructor of Mesh using a vector of SHapeVertex
    * \param v : Vector of ShapeVertex
	*/
	//Mesh(std::vector<ShapeVertex>);

	/**
	* \brief getter of the pointer that leads us to the shapeVertex
    * \return : the pointer that leads us to the shapeVertex
	*/
	//*ShapeVertex getDataPointer();

	/**
	* \brief getter of the number of Vertex of the Mesh
    * \return : the number of Vertex of the Mesh
	*/
	//GLsizei getNbVertex();

	/**
	* \brief method that binds the Mesh
	*/
	void bind();

	/**
	* \brief destructor of Mesh
	*/	
	~Mesh();
	
};

#endif