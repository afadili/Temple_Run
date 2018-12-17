/**
* \file Game.hpp
* \brief Declaration of the class "Game"
*/

#ifndef __GAME__HPP
#define __GAME__HPP

#include <iostream>
#include <vector>
#include <fstream> //lire dans les fichiers

#include "GameManager.hpp"

/**
* \class Game
* \brief class hosting the current game
*/

class Game {

protected :
	GameManager m_manager; /*!<  */
	Character m_character; /*!<  */
	vector<Object> m_walls; /*!<  */
	vector<Object> m_ground; /*!<  */
	vector<Stone> m_stone; /*!<  */


public :
	/**
	* \brief constructor
	* \param GameManager : manager oh the game
	*/
	Game(GameManager manager);

	/**
	* \brief create the map from a ppm file
	* \param path : path to the level files
	* \param nbFloor : number of floors in the level
	*/
	void loadMap(const FilePath &path, int nbFloor);

	/**
	* \brief create the map from a ppm file
	* \param file : file for the floor
	*/
	void loadFloor(const FilePath &file);
};

#endif