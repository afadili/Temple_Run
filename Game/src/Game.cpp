#include <Game/Game.hpp>

Game::Game(GameManager){

}

void Game::loadMap(const FilePath &path, int nbFloor){

	for(int i = 0; i<nbFloor ; i++){
		loadFloor(path + std::to_string(i) + ".txt");
	}
}

void Game::loadFloor(const FilePath &file){
	ifstream fileLevel("file/1.txt");  //Ouverture d'un fichier en lecture

	int w, h, i, j, r, g, b, max;

	//If we can read the file
	if(fileLevel){

		//First line with p3
		string line;
		getline(fileLevel, line);

		//Second line with width and height
		fileLevel.get(w);
		fileLevel.get(h);

		//Third line with maximal color value
		fileLevel.get(max);

		for(i=0 ; i<h; i++){
			for(j=0 ; j<w j++){
				fileLevel.get(r);
				fileLevel.get(g);
				fileLevel.get(b);


			}
		}

	}
	//If we can't read it
	else{
	    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
}