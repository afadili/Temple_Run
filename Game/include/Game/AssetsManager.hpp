/**
 * \file AssetsManager.hpp
 * \brief Declaration of the class "AssetsManager"
 */

#ifndef __ASSETSMANAGER__HPP
#define __ASSETSMANAGER__HPP

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

#include <json/json.h>
#include <Mesh/Mesh.hpp>
#include <Mesh/Cube.hpp>
#include <Error/Error.hpp>

/**
 * \class AssetsManager
 * \brief The manager of all assets. Make sure you have initialized your OpenGL context before.
 */
class AssetsManager {
protected:
  std::map<std::string, ShaderManager*> m_shaders; /*!< map of any possible shaders */
  std::map<std::string, Mesh*> m_meshs; /*!< map of any possible mesh */
  std::map<std::string, Texture*> m_textures; /*!< map of any possible loaded texture */

public:
  /**
   * \brief constructor of the AssetsManager
   * \param assetPath : the json file with all assets (meshs, textures and shaders)
   */
  AssetsManager(const FilePath &assetPath);

  /**
   * \brief destructor of the AssetsManager, delete all loaded assets
   */
  ~AssetsManager();

  /**
   * \brief Load all assets declared in assets file
   * \param assetPath : the json file with all assets (meshs, textures and shaders)
   */
  void loadAssets(const FilePath &assetPath);

  /**
   * \brief Unload all assets (clear the map list and unload data)
   */
  void unloadAssets();

  /**
   * \brief Load all shaders data
   * \param jsonShaders : the json value (parsing with parseFromStream) with shaders data
   */
  void loadShaders(const Json::Value &jsonShaders);

  /**
   * \brief Load a shader data, print warning if error
   * \param jsonShader : the json value (parsing with parseFromStream) with the shaders data
   */
  void loadShader(const Json::Value &jsonShader);

  /**
   * \brief Unload all shaders (clear the map list and unload data)
   */
  void unloadShaders();

  /**
   * \brief Load all textures data
   * \param jsonTextures : the json value (parsing with parseFromStream) with textures data
   */
  void loadTextures(const Json::Value &jsonTextures);

  /**
   * \brief Load a texture data, print warning if error
   * \param jsonTextures : the json value (parsing with parseFromStream) with the texture data
   */
  void loadTexture(const Json::Value &jsonTexture);

  /**
   * \brief Unload all textures (clear the map list and unload data)
   */
  void unloadTextures();

  /**
   * \brief Load all meshs data
   * \param jsonMeshs : the json value (parsing with parseFromStream) with meshs data
   */
  void loadMeshs(const Json::Value &jsonMeshs);

  /**
   * \brief Load a mesh data, print warning if error
   * \param jsonMesh : the json value (parsing with parseFromStream) with the mesh data
   */
  void loadMesh(const Json::Value &jsonMesh);

  /**
   * \brief Unload all meshs (clear the map list and unload data)
   */
  void unloadMeshs();

  /**
   * \brief Opérateur << for print AssetsManager data
   */
  friend std::ostream &operator<<(std::ostream &os, const AssetsManager &am) {
    // Print loaded shaders name
    os << "  -- Loaded Shaders = [ ";
    for (std::pair<std::string, ShaderManager*> map : am.m_shaders)
      os << map.first << " ";
    os << "]\n";

    // Print loaded textures name
    os << "  -- Loaded Textures = [ ";
    for (std::pair<std::string, Texture*> map : am.m_textures)
      os << map.first << " ";
    os << "]\n";

    // Print loaded meshs name
    os << "  -- Loaded Meshs = [ ";
    for (std::pair<std::string, Mesh*> map : am.m_meshs)
      os << map.first << " ";
    os << "]\n";
    return os;
  }
};

#endif