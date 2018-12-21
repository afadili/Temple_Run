#include <Game/Game.hpp>
#include <glimac/FilePath.hpp>

using namespace glimac;

Game::Game(AssetsManager *assets, const FilePath &path, int nbFloor) : m_assets(assets) {
  loadMap(path, nbFloor);
}

void Game::loadMap(const FilePath &path, int nbFloor) {

  /*for(int i = 0; i<nbFloor; i++){
          loadFloor(path + std::to_string(i) + ".ppm");
  }*/
}

void Game::loadFloor(const FilePath &file, int floor) {
  std::ifstream fileLevel(file);

  if (fileLevel.fail())
    throw Error("The ppm file \"" + file.str() + "\" is not found !", "FILE_NOT_FOUND", true);

  if (file.ext() != "ppm")
    throw Error("The file \"" + file.str() + "\" as to be a PPM file !", "INCORRECT_FILE", true);

  int w, h, i, j, r, g, b, max, level;

  //First line with p3
  std::string line;
  getline(fileLevel, line);

  //Second line with width, height and floor of the map
  fileLevel >> w;
  fileLevel >> h;

  //Third line with maximal color value
  fileLevel >> max;

  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      fileLevel >> r;
      fileLevel >> g;
      fileLevel >> b;

      // GROUND
      if (r == 143 && g == 94 && b == 10) {
        /*if (!m_objects["wall"])
          m_objects.insert(std::make_pair("wall", m_assets->));*/
      }

      // WALL
      if (r == 143 && g == 136 && b == 131) {
        //std::cout << "Grey" << std::endl;
        //std::cout << "Wall" << std::endl;					
      }

      if (r == 152 && g == 21 && b == 49) {
        //std::cout << "Burgundy" << std::endl;
        //std::cout << "Hole" << std::endl;					
      }

      if (r == 255 && g == 207 && b == 171) {
        //std::cout << "Beige" << std::endl;
        //std::cout << "Rock" << std::endl;					
      }

      if (r == 0 && g == 0 && b == 0) {
        //std::cout << "Black" << std::endl;
        //std::cout << "Camera" << std::endl;					
      }

      if (r == 39 && g == 203 && b == 205) {
        //std::cout << "Turquoise" << std::endl;
        //std::cout << "Character" << std::endl;					
      }

      if (r == max && g == 0 && b == 0) {
        //std::cout << "Red" << std::endl;					
        //std::cout << "Reality Stone" << std::endl;			
      }

      if (r == 0 && g == max && b == 0) {
        //std::cout << "Green" << std::endl;
        //std::cout << "Time Stone" << std::endl;				
      }

      if (r == 0 && g == 0 && b == max) {
        //std::cout << "Blue" << std::endl;
        //std::cout << "Space Stone" << std::endl;				
      }

      if (r == max && g == max && b == 0) {
        //std::cout << "Yellow" << std::endl;
        //std::cout << "Mind Stone" << std::endl;					
      }

      if (r == max && g == 0 && b == max) {
        //std::cout << "Purple" << std::endl;
        //std::cout << "Power Stone" << std::endl;					
      }

      if (r == max && g == 162 && b == 0) {
        //std::cout << "Orange" << std::endl;
        //std::cout << "Soul Stone" << std::endl;					
      }
    }
  }
}