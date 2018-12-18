/**
* \file IBO.hpp
* \brief description : Declaration of the class "IBO"
*/

#ifndef __IBO__HPP
#define __IBO__HPP

#include "Render.hpp"

/**
* \class IBO
* \brief class defining a IBO and associated actions
*/

class IBO : public Render {

public:
	/**
	* \brief constructor
	*/
	IBO();

	/**
	* \brief destructor
	*/
	~IBO();

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
	void fillBuffer(std::vector<type> &vect);

};

#endif