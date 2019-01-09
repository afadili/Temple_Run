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

void GameManager::unloadLevel() {
  if (!m_currentLevel)
    return;
  m_currentLevel->clear();
  m_currentLevel->resetScore();
  m_currentLevel = nullptr;
}

GameManager::~GameManager() {
  // delete all levels
  for (std::pair<std::string, Level*> lvl : m_levels)
    delete lvl.second;

  // delete all assets
  if (m_assets)
    delete m_assets;
}

void GameManager::eventManager(const SDL_Event &event) {
  // if a game is in progress
  if (m_currentLevel != nullptr)
    m_currentLevel->eventManager(event);
}

void GameManager::update() {
  // if a game is in progress
  if (m_currentLevel != nullptr) {
    // MATRICES de transformations
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), m_config->defaultWidth() / float(m_config->defaultWidth() * 1. / m_config->ratio()), m_config->nearVision(), m_config->farVision());
    switch (m_currentLevel->update(ProjMatrix)) {
      case 1:
        // WIN
        std::cout << "YOU WIN WITH " << m_currentLevel->score() << " PTS !" << std::endl;
        unloadLevel();
        break;
      case 2:
        // LOSE
        std::cout << "YOU LOSE WITH " << m_currentLevel->score() << " PTS !" << std::endl;
        unloadLevel();
        break;
      default:
        break;
    }
  } else {

    // MENUUUUUUUUUUUUUUUU
    Menu menu(m_assets);

    menu.drawMenu();

    loadLevel("level1");

  }


}