/**
 * \file Game.hpp
 * \brief Declaration of the class "Game"
 */

#ifndef __GAME__HPP
#define __GAME__HPP

#include <iostream>
#include <vector>
#include <fstream> 
#include <glimac/FilePath.hpp>

#include <Error/Error.hpp>
#include <Element/ObjectList.hpp>

#include "AssetsManager.hpp"

/// \class VectorD
/// \brief class defining a vector for linear algebra operations.

using namespace glimac;

class Game {
protected:
  AssetsManager *m_assets; /*!< Pointer on the manager of all assets */
  std::map<std::string, ObjectList> m_objects; /*!< map of all objects in the map */
  //Character m_character; /*!<  */
  //std::vector<Object> m_walls; /*!<  */
  //std::vector<Object> m_ground; /*!<  */
  //std::vector<Stone> m_stone; /*!<  */


public:
  /**
   * \brief constructor
   */
  Game(AssetsManager *assets, const FilePath &path, int nbFloor);

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

  /**
   * \brief draw all element of the level game
   * \param ProjMatrix : the projection matrix
   * \param ViewMatrix : view matrix of the camera, identity matrix by default
   */
  void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix = glm::mat4()) const;
};

#endif