/**
 * \file AssetsManager.hpp
 * \brief Declaration of the class "AssetsManager"
 */

#ifndef __ASSETSMANAGER__HPP
#define __ASSETSMANAGER__HPP

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

#include <glimac/FilePath.hpp>

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
  std::map<std::string, std::string> m_objectsType; /*!< map of all object type (second) and associated mesh name (first) */
  std::map<std::vector<int>, std::string> m_objectsCode; /*!< map of all the color identifiers of objects */

public:
  /**
   * \brief constructor of the AssetsManager
   * \param assetPath : the json file with all assets (meshs, textures and shaders)
   */
  AssetsManager(const glimac::FilePath &assetPath);

  /**
   * \brief destructor of the AssetsManager, delete all loaded assets
   */
  ~AssetsManager();

  /**
   * \brief Load all assets declared in assets file
   * \param assetPath : the json file with all assets (meshs, textures and shaders)
   */
  void loadAssets(const glimac::FilePath &assetPath);

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
   * \brief Getter of a shader
   * \param the shader identifier in the map
   * \return the mesh
   */
  ShaderManager *shader(const std::string &name) const;

  /**
   * \brief Getter of a texture
   * \param the texture identifier in the map
   * \return the mesh
   */
  Texture *texture(const std::string &name) const;

  /**
   * \brief Getter of a mesh
   * \param the mesh name
   * \return the mesh
   */
  Mesh *mesh(const std::string &name) const;

  /**
   * \brief Getter of a mesh using his code 
   * \param vec : the mesh identifier in the map
   * \return the mesh or null if not found
   */
  Mesh *mesh(const std::vector<int> &vec) const;

  /**
   * \brief Getter of a mesh using his code 
   * \param r,g,b : the mesh identifier in the map
   * \return the mesh or null if not found
   */
  Mesh *mesh(const int r, const int g, const int b) const;

  /**
   * \brief Getter of a meshName using his code 
   * \param vec : the mesh identifier in the map
   * \return the mesh name or empty if not found
   */
  std::string meshName(const std::vector<int> &vec) const;

  /**
   * \brief Getter of a mesh using his code 
   * \param name: the mesh identifier in the map
   * \return the mesh name or empty if not found
   */
  std::string meshName(const int r, const int g, const int b) const;

  /**
   * \brief Getter of a meshType using his meshName 
   * \param meshName : the mesh name
   * \return the mesh type or empty if not found
   */
  std::string meshType(const std::string &meshName) const;

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