#include <Game/AssetsManager.hpp>

AssetsManager::AssetsManager(const glimac::FilePath &assetPath) {
  loadAssets(assetPath);
}

AssetsManager::~AssetsManager() {
  unloadAssets();
}

void AssetsManager::loadAssets(const glimac::FilePath &assetPath) {
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

void AssetsManager::unloadAssets() {
  unloadMeshs();
  unloadTextures();
  unloadShaders();
}

void AssetsManager::loadShaders(const Json::Value &jsonShaders) {
  if (!jsonShaders)
    throw Error("No shaders data found !", "DATA_NOT_FOUND", true);

  for (Json::Value const& value : jsonShaders) {
    loadShader(value);
  }
}

void AssetsManager::loadShader(const Json::Value &jsonShader) {
  std::string vs = jsonShader["vs"].asString();
  std::string fs = jsonShader["fs"].asString();

  try {
    ShaderManager *shader = new ShaderManager(vs, fs);
    shader->use();
    shader->addUniform("uMVPMatrix");
    shader->addUniform("uMVMatrix");
    shader->addUniform("uNormalMatrix");
    shader->addUniform("uTexture");
    m_shaders.insert(std::make_pair(jsonShader["name"].asString(), shader));
  } catch (const std::exception& err) {
    // if error in ShaderManager, we create and show a specific warning
    std::string message = err.what();
    message += ", the default shader will be used";
    std::cout << Error(message, "SHADER_ERROR").what() << std::endl;
  }
}

void AssetsManager::unloadShaders() {
  for (std::pair<std::string, ShaderManager*> map : m_shaders)
    delete map.second;
  m_shaders.clear();
}

void AssetsManager::loadTextures(const Json::Value &jsonTextures) {
  if (!jsonTextures)
    throw Error("No textures data found !", "DATA_NOT_FOUND");

  for (Json::Value const& value : jsonTextures) {
    loadTexture(value);
  }
}

void AssetsManager::loadTexture(const Json::Value &jsonTexture) {
  try {
    Texture *texture = new Texture(jsonTexture["src"].asString());
    m_textures.insert(std::make_pair(jsonTexture["name"].asString(), texture));
  } catch (const std::exception& err) {
    std::cout << err.what() << std::endl;
  }
}

void AssetsManager::unloadTextures() {
  for (std::pair<std::string, Texture*> map : m_textures)
    delete map.second;
  m_textures.clear();
}

void AssetsManager::loadMeshs(const Json::Value &jsonMeshs) {
  if (!jsonMeshs)
    throw Error("No meshs data found !", "DATA_NOT_FOUND");

  for (Json::Value const& value : jsonMeshs) {
    loadMesh(value);
  }
}

void AssetsManager::loadMesh(const Json::Value &jsonMesh) {
  try {
    Mesh *obj;
    std::string type = jsonMesh["type"].asString();

    // Try to load texture and shader for the mesh, if we can't, we asign the default shader
    ShaderManager *shader = m_shaders[jsonMesh["shader"].asString()];
    Texture *texture = m_textures[jsonMesh["texture"].asString()];
    if (shader == nullptr) { // shader not found
      std::cout << Error("The shader " + jsonMesh["shader"].asString() + " was not found, the default shader was loaded instead", "DATA_NOT_FOUND").what() << std::endl;
      shader = m_shaders["default"];
    } else { // shader found
      if (texture == nullptr) { // texture not found
        std::cout << Error("The texture " + jsonMesh["texture"].asString() + " was not found, the default shader was loaded instead", "DATA_NOT_FOUND").what() << std::endl;
        shader = m_shaders["default"];
      }
    }

    // Create the mesh object
    if (type == "Cube" || type == "cube") {
      if (jsonMesh["size"]) {
        obj = new Cube(glm::vec3(jsonMesh["size"][0].asFloat(), jsonMesh["size"][1].asFloat(), jsonMesh["size"][2].asFloat()), shader, texture);
      } else {
        obj = new Cube(shader, texture);
      }
    } else {
      obj = new Mesh(shader, texture);
      if (jsonMesh["path"])
        obj->loadObj(jsonMesh["path"].asString());
    }

    // Initialisation
    obj->fillBuffers();
    m_meshs.insert(std::make_pair(jsonMesh["name"].asString(), obj));

    // Object code
    if (jsonMesh["code"]) {
      std::vector<int> code(3);
      for (int i = 0; i < 3; i++)
        code[i] = jsonMesh["code"][i].asInt();
      m_objectsCode.insert(std::make_pair(code, jsonMesh["name"].asString()));
    }
  } catch (const std::exception& err) {
    std::cout << err.what() << std::endl;
  }
}

void AssetsManager::unloadMeshs() {
  for (std::pair<std::string, Mesh*> map : m_meshs)
    delete map.second;
  m_meshs.clear();
}

ShaderManager *AssetsManager::shader(const std::string &name) const {
  if (m_shaders.find(name) == m_shaders.end())
    throw Error("The shader " + name + " is not found !", "ASSET_NOT_FOUND", true);
  return m_shaders.at(name);
}

Texture *AssetsManager::texture(const std::string &name) const {
  if (m_textures.find(name) == m_textures.end())
    throw Error("The texture " + name + " is not found !", "ASSET_NOT_FOUND", true);
  return m_textures.at(name);
}

Mesh *AssetsManager::mesh(const std::string &name) const {
  if (m_meshs.find(name) == m_meshs.end())
    throw Error("The mesh \"" + name + "\" is not found !", "ASSET_NOT_FOUND", true);
  return m_meshs.at(name);
}

std::string AssetsManager::meshName(const std::vector<int> &vec) const {
  if (m_objectsCode.find(vec) == m_objectsCode.end())
    return std::string();
  return m_objectsCode.at(vec);
}

std::string AssetsManager::meshName(const int r, const int g, const int b) const {
  return meshName(std::vector<int>{r, g, b});
}
