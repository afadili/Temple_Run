/**
* \file:  Camera.hpp
* \brief Decalaration of the class "Mesh"
*/

#ifndef __MESH__HPP
#define __MESH__HPP

#include <iostream>
#include "Texture.hpp"
#include "Shader.hpp"
#include <vector>
#include <string>


class Mesh
{
private : 

	glm::vec3 m_position;    /*!< position of the camera */


public:
	/**
	* \brief constructor of Camera
	*/
	Camera();

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
	void readEvent(const SDL_Event &e);

	/**
	* \brief destructor of Camera
	*/	
	~Camera();
	
};