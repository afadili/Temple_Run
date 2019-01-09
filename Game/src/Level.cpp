#include <Game/Level.hpp>

Level::Level(const AssetsManager *assets, const glimac::FilePath &path, int nbFloor, int width, int height) : m_assets(assets), m_path(path), m_nbFloor(nbFloor), m_width(width), m_height(height) {
  for (int i = 0; i < nbFloor; i++)
    m_grid.push_back(Eigen::SparseMatrix<Object*>(width, height));
}

void Level::loadMap() {
  // Load each floor
  for (int i = 0; i < m_nbFloor; i++) {
    std::string file("floor_" + std::to_string(i) + ".ppm");
    loadFloor(m_path + file, i);
  }

  // If there is no character in the level
  if (!m_character)
    throw Error("No spawn point found in this level !", "LEVEL_ERROR", true);

  // Initialize the camera
  m_cam.distance() = -m_config["viewDistance"];
  m_cam.rotate(m_character->rotation().y);
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

        // OBSTACLE
        if (meshType == "Obstacle" || meshType == "obstacle") {
          obj = new Obstacle(mesh, glm::vec3(j, floor, i));
        }// STONE
        else if (meshType == "Stone" || meshType == "stone") {
          obj = new Stone(mesh, glm::vec3(j, floor, i));
        }// TURN LEFT
        else if (meshType == "LeftTurn" || meshType == "lefttrun") {
          obj = new LeftTurn(mesh, glm::vec3(j, floor, i));
        }// TURN RIGHT
        else if (meshType == "RightTurn" || meshType == "rightturn") {
          obj = new RightTurn(mesh, glm::vec3(j, floor, i));
        }// FINISHING LINE
        else if (meshType == "FinishingLine" || meshType == "finishingline") {
          obj = new FinishingLine(mesh, glm::vec3(j, floor, i));
        }// CHARACTER
        else if (meshType == "Character" || meshType == "character") {
          m_character = new Character(mesh, glm::vec3(j, floor + 0.25, i));

          // CHARACTER CONFIGURATION
          if (m_config["speed"])
            m_character->speed() = m_config["speed"];
          if (m_config["jumpSpeed"])
            m_character->jumpSpeed() = m_config["jumpSpeed"];
          if (m_config["maxJump"])
            m_character->maxJump() = m_config["maxJump"];

          // CHARACTER DEFAULT ORIENTATION
          if (m_config["startDirection"])
            m_character->direction(glm::vec3(m_config["startDirectionX"], m_config["startDirectionY"], m_config["startDirectionZ"]));

          obj = m_character;
        }// DEFAULT
        else {
          obj = new Object(mesh, glm::vec3(j, floor, -i));
        }

        // Add the object to its list
        m_objects.at(meshName).add(obj);

        // Add the object to the grid
        m_grid[floor].coeffRef(j, i) = obj;
      }
    }
  }
}

void Level::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix) const {
  for (auto const& mapObj : m_objects)
    mapObj.second.draw(ProjMatrix, ViewMatrix);
}

void Level::eventManager(const SDL_Event &event) {
  // EVENT ON CAMERA
  m_cam.eventManager(event);

  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_c) {

    }
  }

}

int Level::update(const glm::mat4 &ProjMatrix) {

  // CAMERA UPDATE
  m_cam.update(m_character->position());

  // RUNNING OBSTACLES
  bool isRunning = true; // if the character have to run or not
  Object *frontObject1 = grid(m_character->gridPosition(0, 0, 1));
  Object *frontObject2 = grid(m_character->gridPosition(0, 1, 1));

  if (frontObject1) {
    if (frontObject1->type() == "Obstacle")
      isRunning = false;
    else if (frontObject1->type() == "Stone")
      addStone(frontObject1);
  }
  if (frontObject2) {
    if (frontObject2->type() == "Obstacle")
      isRunning = false;
  }

  if (isRunning)
    m_character->run();

  draw(ProjMatrix, m_cam.getViewMatrix());

  return 0;
}

void Level::addStone(Object *stone) {
  if (!stone)
    return;
  m_score++;
  removeObject(stone);
}

void Level::removeObject(Object *obj) {
  std::vector<int> vec = obj->gridPosition(); // get obj position
  std::cout << vec[0] << "  " << vec[1] << "  " << vec[2] << "  " << std::endl;
  removeGridObject(vec); // remove from the grid
  m_objects.at(obj->mesh()->name()).remove(obj);
}