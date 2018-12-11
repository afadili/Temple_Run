/**
* \file VAO.hpp
* \brief description : Declaration of the class "VAO"
*/

#ifndef __VAO__HPP
#define __VAO__HPP

#include <iostream>
#include "VBO.hpp"
//#include "IBO.hpp"

/**
* \class VAO
* \brief class defining a VAO and associated actions
*/

class VAO : public Render {

public :
	/**
	* \brief constructor
	*/
	VAO();

	/**
	* \brief destructor
	*/
	~VAO();

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