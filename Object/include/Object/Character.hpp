/**
* \file Character.hpp
* \brief Declaration of the class "Character"
*/

#ifndef __CHARACTER__HPP
#define __CHARACTER__HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include "Object.hpp"

/**
* \class Character
* \brief Mother class of the different characters
*/
class Character : public Object {

protected :
	int m_life; /*!< life of the character */
	float m_speed; /*!< speed of the character */

public :
	/**
	* \brief default constructor
	*/

};

#endif