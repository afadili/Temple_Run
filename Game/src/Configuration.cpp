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
    throw Error(errs, "INCORRECT_FILE", true);

  m_assetsFile = glimac::FilePath(root["assetsFile"].asString());

  for (Json::Value const& value : root["levels"]) {
    m_levelsPath.insert(std::make_pair(root["name"].asString(), root["path"].asString()));
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
}
