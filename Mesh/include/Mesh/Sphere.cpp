/**
* \file:  Sphere.hpp
* \brief Decalaration of the class "Sphere"
*/

#ifndef __SPHERE__HPP
#define __SPHERE__HPP

#include <iostream>
#include "Texture.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include <vector>
#include <string>


class Sphere
{
private : 


public:
	/**
	* \brief constructor of Sphere using params
	*/
	Sphere(GLfloat x, GLsizei a, GLsizei b);
	/**
	* \brief constructor of Sphere
	*/
	Sphere();
	/**
	* \brief destructor of Sphere
	*/	
	~Sphere();
	
};