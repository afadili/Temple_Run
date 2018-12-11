/**
* \file VBO.hpp
* \brief description : Declaration of the class "VBO"
*/

#ifndef __VBO__HPP
#define __VBO__HPP

#include <iostream>
#include "Render.hpp"

/**
* \class VBO
* \brief class defining a VBO and associated actions
*/

class VBO : public Render {

public :
	/**
	* \brief constructor
	*/
	VBO();

	/**
	* \brief destructor
	*/
	~VBO();

	/**
	* \brief 
	*/
	void bind();

	/**
	* \brief 
	*/
	void debind();

	/**
	* \brief 
	* \param 
	*/
	void render();

};

#endif