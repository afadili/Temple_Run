/**
 * \file Configuration.hpp
 * \brief Declaration of the class "Configuration"
 */

#ifndef __CONFIGURATION__HPP
#define __CONFIGURATION__HPP

#include <iostream>
#include <fstream>

#include <glimac/FilePath.hpp>

#include <json/json.h>
#include <Error/Error.hpp>

#include "Level.hpp"
#include "AssetsManager.hpp"

/**
 * \class Configuration
 * \brief Stores all the configuration of the program
 */
class Configuration {
protected:
  glimac::FilePath m_configFile; /*!< The path and name of the configuration file */
  glimac::FilePath m_assetsFile; /*!< The path and name of the assets configuration file */
  std::map<std::string, glimac::FilePath> m_levelsPath; /*!< A map of all level folders */
  int m_fps = 60; /*!< Maximum frame per second, default 60 */
  double m_ratio = 16.f / 9.f; /*!< The ratio of the screen, default 16/9 */
  int m_defaultWidth = 800; /*!< The default width of the screen in pixel, default 800px */
  float m_nearVision = 0.1f; /*!< The minimum vision to display, default 0.1 */
  float m_farVision = 100.f; /*!< The maximal vision to display, default 16/9 */

public:
  /**
   * \brief constructor of the Configuration
   * \param configFile : the json file with all the configuration
   */
  Configuration(const glimac::FilePath &configFile);

  /**
   * \brief destructor 
   */
  ~Configuration() = default;

  /**
   * \brief Get a map of all possible configured levels 
   * \param assets : Pointer on the manager of all assets
   * \return a map of all possible levels 
   */
  std::map<std::string, Level*> levels(AssetsManager *assets = nullptr) const;

  /**
   * \brief Get a configured levels 
   * \param path : the path of the level with the config.json file
   * \param assets : Pointer on the manager of all assets
   * \return A pointer to the level
   */
  Level* level(const glimac::FilePath &path, AssetsManager *assets = nullptr) const;

  /**
   * \brief Getter of m_configFile
   * \return the config file path
   */
  inline
  glimac::FilePath configFile() const {
    return m_configFile;
  }

  /**
   * \brief Getter of m_assetsFile
   * \return the assets file path
   */
  inline
  glimac::FilePath assetsFile() const {
    return m_assetsFile;
  }

  /**
   * \brief Getter of m_fps
   * \return the fps number
   */
  inline
  int fps() const {
    return m_fps;
  }

  /**
   * \brief Getter of m_ratio
   * \return The ratio of the screen
   */
  inline
  double ratio() const {
    return m_ratio;
  }

  /**
   * \brief Getter of m_defaultWidth
   * \return The default width of the screen in pixel
   */
  inline
  int defaultWidth() const {
    return m_defaultWidth;
  }

  /**
   * \brief Getter of m_nearVision
   * \return The minimum vision to display
   */
  inline
  float nearVision() const {
    return m_nearVision;
  }

  /**
   * \brief Getter of m_farVision
   * \return The maximal vision to display
   */
  inline
  float farVision() const {
    return m_farVision;
  }

  /**
   * \brief Opérateur << for print Configuration data
   */
  friend std::ostream &operator<<(std::ostream &os, const Configuration &conf) {
    os << "  -- configuration File = " << conf.m_configFile << " \n";
    os << "  -- assets File = " << conf.m_assetsFile << "\n";
    os << "  -- Levels = {\n";
    for (std::pair<std::string, glimac::FilePath> map : conf.m_levelsPath)
      os << "    -- " << map.first << " = " << map.second << "\n";
    os << "  }\n";
    os << "  -- fps = " << conf.m_fps << "\n";
    os << "  -- ratio = " << conf.m_ratio << "\n";
    os << "  -- nearVision = " << conf.m_nearVision << "\n";
    os << "  -- farVision = " << conf.m_nearVision << "\n";
    return os;
  }
};

#endif