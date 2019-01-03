#include <Game/Configuration.hpp>

Configuration::Configuration(const glimac::FilePath &configFile) : m_configFile(configFile) {
  std::ifstream configJSON(configFile, std::ifstream::binary);
  if (configJSON.fail())
    throw Error("The configuration file \"" + configFile.str() + "\" is not found !", "FILE_NOT_FOUND", true);

  if (configFile.ext() != "json")
    throw Error("The file \"" + configFile.str() + "\" as to be a JSON file !", "INCORRECT_FILE", true);

  Json::Value root; // will contain the root value after parsing.
  Json::CharReaderBuilder builder;
  std::string errs;

  if (!Json::parseFromStream(builder, configJSON, &root, &errs))
    throw Error("On file \"" + configFile.str() + "\"\n" + errs, "INCORRECT_FILE", true);

  m_assetsFile = glimac::FilePath(root["assetsFile"].asString());

  for (Json::Value const& value : root["levels"]) {
    m_levelsPath.insert(std::make_pair(value["name"].asString(), value["path"].asString()));
  }

  if (root["fps"])
    m_fps = root["fps"].asInt();

  if (root["ratio"])
    m_ratio = root["ratio"].asFloat();

  if (root["defaultWidth"])
    m_defaultWidth = root["defaultWidth"].asInt();

  if (root["nearVision"])
    m_nearVision = root["nearVision"].asFloat();

  if (root["farVision"])
    m_farVision = root["farVision"].asFloat();

  if (root["viewDistance"])
    m_viewDistance = root["viewDistance"].asFloat();

}

std::map<std::string, Level*> Configuration::levels(AssetsManager *assets) const {
  std::map<std::string, Level*> levels;
  for (std::pair<std::string, glimac::FilePath> map : m_levelsPath) {
    levels.insert(std::make_pair(map.first, level(map.second, assets)));
  }
  return levels;
}

Level* Configuration::level(const glimac::FilePath &path, AssetsManager *assets) const {
  std::ifstream levelJSON(path + "config.json", std::ifstream::binary);
  if (levelJSON.fail())
    throw Error("The level configuration file (config.json) is not found in \"" + path.str() + "\" !", "FILE_NOT_FOUND", false);

  Json::Value root;
  Json::CharReaderBuilder builder;
  std::string errs;

  if (!Json::parseFromStream(builder, levelJSON, &root, &errs))
    throw Error("On file \"" + path.str() + "\"\n" + errs, "INCORRECT_FILE", false);

  if (!root["floor"])
    throw Error("Missing \"floor\" data to \"" + path.str() + "\"", "INCORRECT_FILE", false);

  if (!root["width"])
    throw Error("Missing \"width\" data to \"" + path.str() + "\"", "INCORRECT_FILE", false);

  if (!root["height"])
    throw Error("Missing \"height\" data to \"" + path.str() + "\"", "INCORRECT_FILE", false);

  return new Level(assets, path, root["floor"].asInt(), root["width"].asInt(), root["height"].asInt());
}
