/**
* \file VAO.hpp
* \brief description : Declaration of the class "VAO"
*/

#ifndef __VAO__HPP
#define __VAO__HPP

#include "Render.hpp"
#include "VBO.hpp"

/**
* \class VAO
* \brief class defining a VAO and associated actions
*/

class VAO : public Render {

public:
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
	template <typename type>
	void fillBuffer(std::vector<type> &vect, VBO *vbo);

};

#endif