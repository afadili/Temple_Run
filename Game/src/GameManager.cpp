#include <Game/GameManager.hpp>

GameManager::GameManager(const FilePath &assetPath) : m_assets(new AssetsManager(assetPath)) {
}

GameManager::~GameManager() {

}