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

#include <json/json.h>
#include <Mesh/Mesh.hpp>
#include <Mesh/Cube.hpp>
#include <Error/Error.hpp>

#include <Game/AssetsManager.hpp>


class Game;

/**
 * \class GameManager
 * \brief The manager of the all the game. Make sure you have initialized your OpenGL context before.
 */
class GameManager {
protected:
  Game *m_currentGame; /*!< Pointer on the current game, null if no game has started */
  AssetsManager m_assets; /*!< The manager of all assets */

public:
  /**
   * \brief constructor of the GameManager
   * \param assetPath : the json file with all assets (meshs, textures and shaders)
   */
  GameManager(const FilePath &assetPath);

  /**
   * \brief destructor of the GameManager, delete all loaded assets
   */
  ~GameManager();

  /**
   * \brief Opérateur << for print GameManager data
   */
  friend std::ostream &operator<<(std::ostream &os, const GameManager &gm) {
    // Print loaded shaders name
    os << "-- Assets = [\n";
    os << gm.m_assets;
    os << "]\n";
  }
};

#endif