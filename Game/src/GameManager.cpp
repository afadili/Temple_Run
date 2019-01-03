#include <Game/GameManager.hpp>

GameManager::GameManager(const Configuration *config) : m_config(config) {
  m_assets = new AssetsManager(m_config->assetsFile());
  setLevelsMap();
}

void GameManager::setLevelsMap() {
  m_levels = m_config->levels(m_assets);
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

void GameManager::update(const SDL_Event &event) {
  // if a game is in progress
  if (m_currentLevel != nullptr) {
    // MATRICES de transformations
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), m_config->defaultWidth() / float(m_config->defaultWidth() * 1. / m_config->ratio()), m_config->nearVision(), m_config->farVision());
    switch (m_currentLevel->update(event, ProjMatrix)) {
      case 1:
        // WIN
        break;
      case 2:
        // LOSE
        break;
      default:
        break;
    }
  } else {

    // MENUUUUUUUUUUUUUUUU
  Menu menu;

  menu.drawMenu();

    loadLevel("level2");

  }


}