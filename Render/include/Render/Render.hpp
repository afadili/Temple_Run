/**
* \file Render.hpp
* \brief description : Declaration of the class "Render"
*/

#ifndef __VAO__HPP
#define __VAO__HPP

#include <iostream>
#include <vector>

/**
* \class Render
* \brief class 
*/

class Render {

protected :
	Gluint m_ID{}; /*!< id of the object (vao, vbo..) */

public :
	/**
	* \brief default constructor
	*/
	Render() = default;

	/**
	* \brief
	* \param 
	*/
	void setId(Gluint id);

	/**
	* \brief
	* \param  
	*/
	Gluint getId(Gluint id);

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