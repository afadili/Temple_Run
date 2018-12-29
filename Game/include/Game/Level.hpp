/**
 * \file Level.hpp
 * \brief Declaration of the class "Level"
 */

#ifndef __LEVEL__HPP
#define __LEVEL__HPP

#include <iostream>
#include <vector>
#include <fstream> 
#include <glimac/FilePath.hpp>

#include <Error/Error.hpp>
#include <Element/ObjectList.hpp>

#include "AssetsManager.hpp"

/**
 * \class Level
 * \brief The manager for a level game
 */
class Level {
protected:
  glimac::FilePath m_path; /*!< The level folder */
  AssetsManager *m_assets; /*!< Pointer on the manager of all assets */
  int m_nbFloor; /*!< floor number of the level (number of ppm files) */
  std::map<std::string, ObjectList> m_objects; /*!< map of all objects in the map */
  int nbFloor; /*!< floor number of level */
  //Character m_character; /*!<  */

public:
  /**
   * \brief constructor
   */
  Level(AssetsManager *assets, const glimac::FilePath &path, int nbFloor);

  /**
   * \brief create the map from all the levels of the decor
   */
  void loadMap();

  /**
   * \brief create a level of the decor from a ppm file
   * \param file : file for the floor
   */
  void loadFloor(const glimac::FilePath &file, const int floor);

  /**
   * \brief draw all element of the level game
   * \param ProjMatrix : the projection matrix
   * \param ViewMatrix : view matrix of the camera, identity matrix by default
   */
  void draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix = glm::mat4()) const;
};

#endif