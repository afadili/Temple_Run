#include <Game/GameManager.hpp>

GameManager::GameManager(const FilePath &assetPath){
	loadAssets(assetPath);
}

void GameManager::loadAssets(const FilePath &assetPath){
	std::ifstream assetJSON(assetPath, std::ifstream::binary);
	if(assetJSON.fail())
		std::cout << "FILE DON'T EXIST" << std::endl;

    Json::Value root;   // will contain the root value after parsing.
    Json::CharReaderBuilder builder;
    std::string errs;

    if (!Json::parseFromStream(builder, assetJSON, &root, &errs)) {
        // report to the user the failure and their locations in the document.
        std::cout  << errs << std::endl;
    }
     

    const Json::Value& shaders = root["shaders"]; // array of characters
    for (int i = 0; i < shaders.size(); i++){
        std::cout << "    name: " << shaders[i]["name"].asString();
        std::cout << "      fs: " << shaders[i]["fs"].asString();
        std::cout << "      vs: " << shaders[i]["vs"].asString();
        std::cout << std::endl;
    }

}