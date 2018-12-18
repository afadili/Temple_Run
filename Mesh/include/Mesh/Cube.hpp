/**
* \file:  Cube.hpp
* \brief Decalaration of the class "Cube"
*/

#ifndef __CUBE__HPP
#define __CUBE__HPP

#include <iostream>
#include <Render/Texture.hpp>
#include <Render/VAO.hpp>
#include <Render/VBO.hpp>
#include <Render/IBO.hpp>
#include <glimac/Shader.hpp>
#include "Mesh.hpp"
#include <vector>
#include <string>


class Cube : public Mesh {
protected:



public:
	/**
	* \brief constructor of Cube using a vector of ShapeVertex
    * \param vertices : vector of ShapeVertex
	*/
	Cube();

	/**
	* \brief constructor of Cube
    * \param shader :
    * \param textures : 
	*/
	Cube(Shader *shader, Texture *texture);

	Cube(const glm::vec3 &width, Shader *shader, Texture *texture);

	Cube() : Mesh(const glm::vec3 &width);



	/**
	* \brief destructor of Cube
	*/	
	~Cube() = default;

	/**
	* \brief getter of the vector of vertices
	*/
	const std::vector<ShapeVertex> &Vertices() const;

	void generateVertices(const glm::vec3 &width);

	void generateIndexs();

	/**
	* \brief setter of id of the object 
	*/
	GLuint &id();


	
};

#endif