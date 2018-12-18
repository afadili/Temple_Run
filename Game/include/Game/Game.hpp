/**
* \file Game.hpp
* \brief Declaration of the class "Game"
*/

#ifndef __GAME__HPP
#define __GAME__HPP

#include <iostream>
#include <vector>
#include <fstream> //lire dans les fichiers
#include <glimac/FilePath.hpp>
#include <Error/Error.hpp>

//#include "GameManager.hpp"

/// \class VectorD
/// \brief class defining a vector for linear algebra operations.

using namespace glimac;

class Game {

protected:
	//GameManager m_manager; /*!<  */
	//Character m_character; /*!<  */
	//std::vector<Object> m_walls; /*!<  */
	//std::vector<Object> m_ground; /*!<  */
	//std::vector<Stone> m_stone; /*!<  */


public:
	/**
	* \brief constructor
	*/
	Game(const FilePath &path, int nbFloor);

	/**
	* \brief create the map from all the levels of the decor
	* \param path : path to the level files
	* \param nbFloor : number of floors in the level
	*/
	void loadMap(const FilePath &path, int nbFloor);

	/**
	* \brief create a level of the decor from a ppm file
	* \param file : file for the floor
	*/
	void loadFloor(const FilePath &file, int floor);
};

#endif