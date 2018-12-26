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

#include "AssetsManager.hpp"
#include "Configuration.hpp"

class Level;

/**
 * \class GameManager
 * \brief The manager of the all the game. Make sure you have initialized your OpenGL context before.
 */
class GameManager {
protected:
  Configuration m_config; /*!<The configuration of the game */
  Level *m_currentLevel = nullptr; /*!< Pointer on the current level, null if no Level has started */
  AssetsManager *m_assets = nullptr; /*!< Pointer on the manager of all assets */

public:
  /**
   * \brief constructor of the GameManager
   * \param assetPath : the json file with the configuration
   */
  GameManager(const FilePath &configPath);

  /**
   * \brief destructor of the GameManager, delete all loaded assets
   */
  ~GameManager();

  /**
   * \brief Load a level and set it in currentLevel
   * \param name : the name of the level in the configuration 
   */
  void loadLevel(const std::string &name);

  /**
   * \brief Getter of the AssetsManager
   * \return m_mesh
   */
  inline
  AssetsManager* assets() const {
    return m_assets;
  }

  /**
   * \brief Opérateur << for print GameManager data
   */
  friend std::ostream &operator<<(std::ostream &os, const GameManager &gm) {
    // Print loaded shaders name
    os << "-- Assets = [\n";
    os << *(gm.m_assets);
    os << "]\n";
  }
};

#endif