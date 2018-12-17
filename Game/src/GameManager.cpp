#include <Game/GameManager.hpp>

GameManager::GameManager(const FilePath &assetPath){
	loadAssets(assetPath);
}

void GameManager::loadAssets(const FilePath &assetPath){
	/*std::ifstream assetJSON(assetPath);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(assetJSON, obj);     // Reader can also read strings
    std::cout << "Last name: " << obj["lastname"].asString() << std::endl;
    std::cout << "First name: " << obj["firstname"].asString() << std::endl;*/
}