/**
* \file Render.hpp
* \brief Declaration of the class "Render"
*/

#ifndef __RENDER__HPP
#define __RENDER__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

/**
* \class Render
* \brief Mother class of rendering management
*/
class Render {

protected :
	GLuint m_ID; /*!< id of the object (vao, vbo..) */

public :
	/**
	* \brief default constructor
	*/
	Render() = default;

	/**
	* \brief getter of id of the object 
	* \param 
	*/
	const GLuint &id() const;

	/**
	* \brief setter of id of the object 
	* \param 
	*/
	GLuint &id();

	/**
	* \brief 
	*/
	virtual void bind(){};

	/**
	* \brief 
	*/
	virtual void debind(){};

};

#endif