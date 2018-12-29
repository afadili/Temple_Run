#include <Game/GameManager.hpp>

GameManager::GameManager(const FilePath &configPath) : m_config(configPath) {
  m_assets = new AssetsManager(m_config.assetsFile());
  setLevelsMap();
}

void GameManager::setLevelsMap() {
  m_levels = m_config.levels(m_assets);
}

void GameManager::loadLevel(const std::string &name) {
  if (!m_levels[name])
    throw Error("The level name \"" + name + "\" is not found !", "LEVEL_ERROR", true);
  m_currentLevel = m_levels.at(name);
  m_currentLevel->loadMap();
}

GameManager::~GameManager() {
  if (m_currentLevel)
    delete m_currentLevel;
  if (m_assets)
    delete m_assets;
}