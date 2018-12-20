#include <Game/GameManager.hpp>

GameManager::GameManager(const FilePath &assetPath) {
  loadAssets(assetPath);
}

GameManager::~GameManager() {
  unloadAssets();
}

void GameManager::loadAssets(const FilePath &assetPath) {
  std::ifstream assetJSON(assetPath, std::ifstream::binary);
  if (assetJSON.fail())
    throw Error("The asset file \"" + assetPath.str() + "\" is not found !", "FILE_NOT_FOUND", true);

  if (assetPath.ext() != "json")
    throw Error("The file \"" + assetPath.str() + "\" as to be a JSON file !", "INCORRECT_FILE", true);

  Json::Value root; // will contain the root value after parsing.
  Json::CharReaderBuilder builder;
  std::string errs;

  if (!Json::parseFromStream(builder, assetJSON, &root, &errs))
    throw Error(errs, "INCORRECT_FILE", true);

  loadShaders(root["shaders"]);
  loadTextures(root["textures"]);
  loadMeshs(root["meshs"]);
}

void GameManager::unloadAssets() {
  unloadMeshs();
  unloadTextures();
  unloadShaders();
}

void GameManager::loadShaders(const Json::Value &jsonShaders) {
  if (!jsonShaders)
    throw Error("No shaders data found !", "DATA_NOT_FOUND", true);

  for (auto const& value : jsonShaders) {
    loadShader(value);
  }
}

void GameManager::loadShader(const Json::Value &jsonShader) {
  std::string vs = jsonShader["vs"].asString();
  std::string fs = jsonShader["fs"].asString();

  try {
    ShaderManager *shader = new ShaderManager(vs, fs);
    m_shaders.insert(std::make_pair(jsonShader["name"].asString(), shader));
  } catch (const std::exception& err) {
    // if error in ShaderManager, we create and show a specific warning
    std::string message = err.what();
    message += ", the default shader will be used";
    std::cout << Error(message, "SHADER_ERROR").what() << std::endl;
  }
}

void GameManager::unloadShaders() {
  for (std::pair<std::string, ShaderManager*> map : m_shaders)
    delete map.second;
  m_shaders.clear();
}

void GameManager::loadTextures(const Json::Value &jsonTextures) {
  if (!jsonTextures)
    throw Error("No textures data found !", "DATA_NOT_FOUND");

  for (auto const& value : jsonTextures) {
    loadTexture(value);
  }
}

void GameManager::loadTexture(const Json::Value &jsonTexture) {
  try {
    Texture *texture = new Texture(jsonTexture["src"].asString());
    m_textures.insert(std::make_pair(jsonTexture["name"].asString(), texture));
  } catch (const std::exception& err) {
    std::cout << err.what() << std::endl;
  }
}

void GameManager::unloadTextures() {
  for (std::pair<std::string, Texture*> map : m_textures)
    delete map.second;
  m_textures.clear();
}

void GameManager::loadMeshs(const Json::Value &jsonMeshs) {
  if (!jsonMeshs)
    throw Error("No textures data found !", "DATA_NOT_FOUND");

  for (auto const& value : jsonMeshs) {
    loadMesh(value);
  }
}

void GameManager::loadMesh(const Json::Value &jsonMesh) {
  try {
    Mesh *obj;
    std::string type = jsonMesh["type"].asString();

    ShaderManager *shader = m_shaders[jsonMesh["shader"].asString()];
    Texture *texture = nullptr;
    if (shader == nullptr) { // shader not found
      std::cout << Error("The shader " + jsonMesh["shader"].asString() + " was not found, the default shader was loaded instead", "DATA_NOT_FOUND").what() << std::endl;
      shader = m_shaders["default"];
    } else { // shader found
      Texture *texture = m_textures[jsonMesh["texture"].asString()];
      if (texture == nullptr) { // texture not found
        std::cout << Error("The texture " + jsonMesh["texture"].asString() + " was not found, the default shader was loaded instead", "DATA_NOT_FOUND").what() << std::endl;
        shader = m_shaders["default"];
      }
    }

    if (type == "Cube" || type == "cube") {
      if (jsonMesh["size"]) {
        obj = new Cube(glm::vec3(jsonMesh["size"][0].asFloat(), jsonMesh["size"][1].asFloat(), jsonMesh["size"][2].asFloat()), shader, texture);
      } else {
        obj = new Cube(shader, texture);
      }
    } else {
      obj = new Mesh(shader, texture);
    }
    m_meshs.insert(std::make_pair(jsonMesh["name"].asString(), obj));
  } catch (const std::exception& err) {
    std::cout << err.what() << std::endl;
  }
}

void GameManager::unloadMeshs() {
  for (std::pair<std::string, Mesh*> map : m_meshs)
    delete map.second;
  m_meshs.clear();
}


