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
#include <GL/glew.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <Mesh/Mesh.hpp>
#include <Mesh/Cube.hpp>
#include <Error/Error.hpp>

#include "AssetsManager.hpp"
#include "Level.hpp"
#include "Configuration.hpp"

/**
 * \class GameManager
 * \brief The manager of the all the game. Make sure you have initialized your OpenGL context before.
 */
class GameManager {
protected:
  const Configuration *m_config; /*!<The configuration of the game */
  Level *m_currentLevel = nullptr; /*!< Pointer on the current level, null if no Level has started */
  std::map<std::string, Level*> m_levels; /*!< A map of all possible levels */
  AssetsManager *m_assets = nullptr; /*!< Pointer on the manager of all assets */

public:
  /**
   * \brief constructor of the GameManager
   * \param config : the configuration of the game
   */
  GameManager(const Configuration *config);

  /**
   * \brief destructor of the GameManager, delete all loaded assets
   */
  ~GameManager();

  /**
   * \brief Main loop of all the game
   * \param event : the sdl event
   */
  void update(const SDL_Event &event);


  /**
   * \brief Set all the possible levels from the configuration
   */
  void setLevelsMap();

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
   * \brief Getter of the current level
   * \return m_mesh
   */
  inline
  Level* level() const {
    return m_currentLevel;
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