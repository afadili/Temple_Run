/**
 * \file Level.hpp
 * \brief Declaration of the class "Level"
 */

#ifndef __LEVEL__HPP
#define __LEVEL__HPP

#include <iostream>
#include <vector>
#include <fstream> 
#include <Eigen/Sparse>

#include <glimac/FilePath.hpp>

#include <Error/Error.hpp>
#include <Element/ObjectList.hpp>
#include <Element/Obstacle.hpp>
#include <Element/Stone.hpp>
#include <Element/Character.hpp>
#include <Element/FinishingLine.hpp>
#include <Element/LeftTurn.hpp>
#include <Element/RightTurn.hpp>

#include <Game/Camera.hpp>

#include "AssetsManager.hpp"

/**
 * \class Level
 * \brief The manager for a level game
 */
class Level {
protected:
  std::map<std::string, float> m_config; /*!< level configuration variable */
  glimac::FilePath m_path; /*!< The level folder */
  const AssetsManager *m_assets; /*!< Pointer on the manager of all assets */
  Character *m_character;
  int m_nbFloor; /*!< floor number of the level (number of ppm files) */
  int m_width; /*!< width of the level */
  int m_height; /*!< height of the level */
  std::map<std::string, ObjectList> m_objects; /*!< map of all objects in the map, for the rendering */
  std::vector<Eigen::SparseMatrix<Object*>> m_grid; /*!< vector of sparse Matrix with all static object in the level */
  unsigned int m_score = 0; /*!< the score of the actual game */
  Camera m_cam; /*!< the camera of the level */

private:
  Level() = default;

public:
  /**
   * \brief constructor
   */
  Level(const AssetsManager *assets, const glimac::FilePath &path, int nbFloor, int width, int height);

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

  /**
   * \brief modification of the level depending on the events
   * \param event : SDL event
   */
  void eventManager(const SDL_Event &event);

  /**
   * \brief update and draw the level, with character controller. Function called at each frame
   * \param ProjMatrix : the projection matrice of the game
   * \return 1 if character win, 2 if loose and 0 otherwise
   */
  int update(const glm::mat4 &ProjMatrix);

  /**
   * \brief add a stone to the score
   * \param stone : the stone 
   */
  void addStone(Object *stone);

  /**
   * \brief remove an object
   * \param obj : the object to remove 
   */
  void removeObject(Object *obj);

  /**
   * \brief getter for level configuration variable
   * \return level configuration variable
   */
  const std::map<std::string, float> &config() const {
    return m_config;
  }

  /**
   * \brief setter for level configuration variable
   * \return level configuration variable
   */
  std::map<std::string, float> &config() {
    return m_config;
  }

  /**
   * \brief Remove an object from the grid
   * \param x : the x position of the grid
   * \param y : the y position of the grid
   * \param z : the z position of the grid
   */
  inline
  void removeGridObject(const int x, const int y, const int z) {
    m_grid[y].coeffRef(x, z) = nullptr;
  }

  /**
   * \brief Remove an object from the grid
   * \param x : the x position of the grid
   * \param y : the y position of the grid
   * \param z : the z position of the grid
   */
  inline
  void removeGridObject(const std::vector<int> &vec) {
    removeGridObject(vec[0], vec[1], vec[2]);
  }

  /**
   * \brief get an static object based on its position in the level 
   * \param x : the x position of the grid
   * \param y : the y position of the grid
   * \param z : the z position of the grid
   * \return pointer on the object or null if empty position
   */
  Object* grid(const int x, const int y, const int z) const {
    if (x < 0, y < 0, z < 0) return nullptr;
    return m_grid[y].coeff(x, z);
  }

  /** \brief get an static object based on its position in the level
   * \param vec : the vector of position (size 3)
   * \return pointer on the object or null if empty position
   */
  inline
  Object* grid(const std::vector<int> &vec) const {
    return grid(vec[0], vec[1], vec[2]);
  }

};

#endif