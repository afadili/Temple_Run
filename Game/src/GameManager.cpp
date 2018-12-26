#include <Game/GameManager.hpp>

GameManager::GameManager(const FilePath &configPath) : m_config(configPath) {
  m_assets = new AssetsManager(m_config.assetsFile());
}

GameManager::~GameManager() {
  if (m_currentLevel)
    delete m_currentLevel;
  if (m_assets)
    delete m_assets;
}