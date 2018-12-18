#include <Game/GameManager.hpp>

GameManager::GameManager(const FilePath &assetPath){
	loadAssets(assetPath);
}

void GameManager::loadAssets(const FilePath &assetPath){
	std::ifstream assetJSON(assetPath, std::ifstream::binary);
	if(assetJSON.fail())
		throw Error("The asset file \"" + assetPath.str() +"\" is not found !", "FILE_NOT_FOUND", true);

	if(assetPath.ext() != "json")
		throw Error("The file \"" + assetPath.str() +"\" as to be a JSON file !", "INCORRECT_FILE", true);

    Json::Value root;   // will contain the root value after parsing.
    Json::CharReaderBuilder builder;
    std::string errs;

    if (!Json::parseFromStream(builder, assetJSON, &root, &errs))
        throw Error(errs, "INCORRECT_FILE", true);
    
    loadShaders(root["shaders"]);


}

void GameManager::loadShaders(const Json::Value &jsonShaders){
	if(!jsonShaders)
		throw Error("No shaders data found !", "DATA_NOT_FOUND", false);

	std::for_each(jsonShaders.begin(), jsonShaders.end(),
	  [](const Json::Value &jsonShader) {
	  	//Shader *shader = new Shader()
	  	//m_shaders.insert(std::make_pair(jsonShader["name"], shader));
		
	});
}

void GameManager::loadMeshs(const Json::Value &jsonMeshs){
	  std::for_each(jsonMeshs.begin(), jsonMeshs.end(),
          [](const Json::Value &mesh) {
        	
      }
  );
}

void loadTextures(const Json::Value &jsonTextures);
