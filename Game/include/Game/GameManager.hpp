/**
* \file GameManager.hpp
* \brief Declaration of the class "GameManager"
*/

#ifndef __GAMEMANAGER__HPP
#define __GAMEMANAGER__HPP

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

#include <Mesh/Mesh.hpp>
#include <Render/Texture.hpp>
#include <glimac/Shader.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/FilePath.hpp>
#include <Error/Error.hpp>
#include <json/json.h>

class Game; 

/**
* \class GameManager
* \brief The manager of the all the game
*/
class GameManager {

protected :
	Game *m_currentGame; /*!< Pointer on the current game, null if no game has started */
	std::map<std::string, Mesh*> m_meshs; /*!< map of any possible mesh */
	std::map<std::string, Texture*> m_textures; /*!< map of any possible loaded texture */
	std::map<std::string, Shader*> m_shaders; /*!<  */

public :
	/**
	* \brief constructor of the GameManager
	* \param assetPath : the json file with all assets (meshs, textures and shaders)
	*/
	GameManager(const FilePath &assetPath);

	/**
	* \brief Load all assets declared in assets file
	* \param assetPath : the json file with all assets (meshs, textures and shaders)
	*/
	void loadAssets(const FilePath &assetPath);

	/**
	* \brief Load all shaders data
	* \param jsonShaders : the json value (parsing with parseFromStream) with shaders data
	*/
	void loadShaders(const Json::Value &jsonShaders);

	/**
	* \brief Load all textures data
	* \param jsonTextures : the json value (parsing with parseFromStream) with textures data
	*/
	void loadTextures(const Json::Value &jsonTextures);

	/**
	* \brief Load all meshs data
	* \param jsonMeshs : the json value (parsing with parseFromStream) with meshs data
	*/
	void loadMeshs(const Json::Value &jsonMeshs);
};

#endif