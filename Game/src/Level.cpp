#include <Game/Level.hpp>

Level::Level(const AssetsManager *assets, const glimac::FilePath &path, int nbFloor, int width, int height) : m_assets(assets), m_path(path), m_nbFloor(nbFloor), m_width(width), m_height(height) {
  for (int i = 0; i < nbFloor; i++)
    m_grid.push_back(Eigen::SparseMatrix<Object*>(width, height));
}

void Level::loadMap() {
  for (int i = 0; i < m_nbFloor; i++) {
    std::string file("floor_" + std::to_string(i) + ".ppm");
    loadFloor(m_path + file, i);
  }
}

void Level::loadFloor(const glimac::FilePath &file, const int floor) {
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

      std::string meshName = m_assets->meshName(r, g, b);

      if (!meshName.empty()) {
        Mesh *mesh = m_assets->mesh(meshName);
        std::string meshType = m_assets->meshType(meshName);

        // If no list of objects has been initialized to this name
        if (m_objects.find(meshName) == m_objects.end())
          m_objects.insert(std::make_pair(meshName, mesh));

        // Create the object
        Object *obj;
        if (meshType == "Obstacle" || meshType == "obstacle") {
          obj = new Obstacle(mesh, glm::vec3(i, -floor, -j));
        } else if (meshType == "Stone" || meshType == "stone") {
          obj = new Stone(mesh, glm::vec3(i, -floor, -j));
        } else if (meshType == "FinishingLine" || meshType == "finishingline") {
          obj = new FinishingLine(mesh, glm::vec3(i, -floor, -j));
        } else if (meshType == "Character" || meshType == "character") {
          m_character = new Character(mesh, glm::vec3(i, -floor - 0.25, -j));
          obj = m_character;
        } else {
          obj = new Object(mesh, glm::vec3(i, -floor, -j));
        }

        // Add the object to its list
        m_objects.at(meshName).add(obj);

        // Add the object to the grid
        m_grid[floor].coeffRef(i, j) = obj;
      }
    }
  }
}

void Level::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix) const {
  for (auto const& mapObj : m_objects)
    mapObj.second.draw(ProjMatrix, ViewMatrix);
}

int Level::update(const SDL_Event &event, const glm::mat4 &ProjMatrix) {
  glm::mat4 ViewMatrix = glm::translate(m_character->MWMatrix(), glm::vec3(2, 0, 0));
  draw(ProjMatrix, ViewMatrix);

  return 0;
}