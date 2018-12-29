/**
* \file Camera.hpp
* \brief Decalaration of the class "Camera"
*/

// Doxygen menu
/// \version 0.1
/// \mainpage
/// \image html myImage.jpg
/// \tableofcontents
/// \section instroduction_sec What for?
/// VectorD is a super tool.
/// \section install_bigsec How to install
/// \subsection dependencies_sec Dependecies
/// \li nothing
/// \li nothing else
/// \li Doxygen (if you want the documentation)
/// \subsection install_sec Install with cmake (Linux)
/// \li go to garamon dir
/// \li mkdir build
/// \li cd build
/// \li cmake ..
/// \li make
/// \li make html
/// \li The documentation is located in [path to build]/doc/doc-doxygen/html/index.html

#ifndef __CAMERA__HPP
#define __CAMERA__HPP

#include <iostream>
#include <glimac/glm.hpp>
#include <vector>
#include <string>

/// \class VectorD
/// \brief class defining a vector for linear algebra operations.

class Camera {
private : 

	glm::vec3 m_position;    /*!< position of the camera */

public:
	/**
	* \brief constructor of Camera
	*/
	Camera();

	/**
	* \brief destructor of Camera
	*/	
	~Camera();

	/**
	* \brief method to move the camera with the character's view
	*/
	void moveUp();

	/**
	* \brief method to move the camera with the character's view
	*/
	void moveDown();

	/**
	* \brief method to move the camera with the character's view
	*/
	void moveForward();

	/**
	* \brief method to move the camera with the character's view
	*/
	void moveRight();

	/**
	* \brief method to move the camera with the character's view
	*/
	void moveLeft();

	/**
	* \brief method that update the position of the camera
	*/
	void Update();

	/**
	* \brief setter that reads the event and will set the camera depending on the event
	*/
	//void readEvent(const SDL_Event &e);

};

#endif