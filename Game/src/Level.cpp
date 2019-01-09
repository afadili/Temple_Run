#include <Game/Level.hpp>

Level::Level(const AssetsManager *assets, const glimac::FilePath &path, int nbFloor, int width, int height) : m_assets(assets), m_path(path), m_nbFloor(nbFloor), m_width(width), m_height(height) {
  for (int i = 0; i < nbFloor; i++)
    m_grid.push_back(Eigen::SparseMatrix<Object*>(width, height));
}

Level::~Level() {
  clear();

  if (m_skybox)
    delete m_skybox;
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
  glm::vec3 eyesPosition(0., m_character->size().y / 2., m_character->size().z / 2.);
  m_cam.initialization(-m_config["viewDistance"], m_character->rotation().y, eyesPosition, m_config["viewMaxAngle"]);
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

      addObject(meshName, j, floor, i);

    }
  }
}

void Level::addObject(const std::string &meshName, int x, int y, int z) {
  if (meshName.empty())
    return;
  Mesh *mesh = m_assets->mesh(meshName);
  if (!mesh)
    return;

  std::string meshType = m_assets->meshType(meshName);

  // If no list of objects has been initialized to this name
  if (m_objects.find(meshName) == m_objects.end())
    m_objects.insert(std::make_pair(meshName, mesh));

  // Create the object
  Object * obj;

  // OBSTACLE
  if (meshType == "Obstacle" || meshType == "obstacle") {
    obj = new Obstacle(mesh, glm::vec3(x, y, z));
  }// STONE
  else if (meshType == "Stone" || meshType == "stone") {
    obj = new Stone(mesh, glm::vec3(x, y, z));
  }// TURN LEFT
  else if (meshType == "LeftTurn" || meshType == "lefttrun") {
    obj = new LeftTurn(mesh, glm::vec3(x, y, z));
  }// TURN RIGHT
  else if (meshType == "RightTurn" || meshType == "rightturn") {
    obj = new RightTurn(mesh, glm::vec3(x, y, z));
  }// FINISHING LINE
  else if (meshType == "FinishingLine" || meshType == "finishingline") {
    obj = new FinishingLine(mesh, glm::vec3(x, y, z));
  }// CHARACTER 
  else if (meshType == "Character" || meshType == "character") {
    m_character = new Character(mesh, glm::vec3(x, y + 0.25, z));

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
  } else {
    // DEFAULT
    obj = new Object(mesh, glm::vec3(x, y, z));
  }

  // Add the object to its list
  m_objects.at(meshName).add(obj);

  // Add the object to the grid
  m_grid[y].coeffRef(x, z) = obj;
}

void Level::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &ViewMatrix) const {
  // OBJECTS
  for (auto const& mapObj : m_objects)
    mapObj.second.draw(ProjMatrix, ViewMatrix);

  // SKYBOX
  if (m_skybox)
    m_skybox->draw(ProjMatrix, ViewMatrix, false);
}

void Level::eventManager(const SDL_Event &event) {
  // EVENT ON CAMERA
  m_cam.eventManager(event);

  // CHARACTER EVENT
  if (event.type == SDL_KEYDOWN) {
    SDLKey key = event.key.keysym.sym;

    // UNDERNEATH OBSTACLES
    Object * underObject = grid(m_character->gridPosition(0, -1, 0));

    // LEFT
    if (key == SDLK_q || key == SDLK_LEFT) {
      if (underObject && underObject->type() == "LeftTurn") { // TURN
        m_character->turnLeft();
        m_cam.rotate(m_character->rotation().y);
      } else { // MOVE IF CAN
        if (!isObstacle(1, 0, 0)) {
          m_character->moveLeft();
        }
      }
    }// RIGHT
    else if (key == SDLK_d || key == SDLK_RIGHT) {
      if (underObject && underObject->type() == "RightTurn") { // TURN
        m_character->turnRight();
        m_cam.rotate(m_character->rotation().y);
      } else { // MOVE IF CAN
        if (!isObstacle(-1, 0, 0)) {
          m_character->moveRight();
        }
      }
    }// JUMP
    else if (key == SDLK_SPACE) {
      if (!isObstacle(0, 1, 0))
        m_character->jump();
    }
  }
}

int Level::update(const glm::mat4 &ProjMatrix) {
  int state = 0; // state of the game (variable of return)
  bool isRunning = true; // if the character have to run or not

  // CAMERA UPDATE
  m_cam.update(m_character->position());

  // OBJECT ON CURRENT POSITION
  for (int i = 0; i <= m_character->size().y; i++) {
    Object * currentObject = grid(m_character->gridPosition(0, i, 1));
    if (currentObject) {
      if (currentObject->type() == "Stone")
        addStone(currentObject);
      else if (currentObject->type() == "FinishingLine")
        state = 1; // WIN
    }
  }

  // FRONT OBSTACLES
  isRunning = !isObstacle(0, 0, 1);

  // UNDERNEATH OBSTACLES
  Object * underObject = grid(m_character->gridPosition(0, -1, 0));
  if (!m_character->isJumping() && (!underObject || underObject->type() == "Water" || underObject->type() == "Lava"))
    state = 2; // LOSE

  // RUNNING
  if (isRunning && state == 0)
    m_character->run();

  // DRAW
  draw(ProjMatrix, m_cam.getViewMatrix());

  return state;
}

bool Level::isObstacle(int x, int y, int z) const {
  for (int i = 0; i <= m_character->size().y; i++) {
    Object * frontObject = grid(m_character->gridPosition(x, i + y, z));
    if (frontObject) {
      if (frontObject->type() == "Obstacle")
        return true;
    }
  }
  return false;
}

void Level::addStone(Object * stone) {
  if (!stone)
    return;
  m_score++;
  removeObject(stone);
}

void Level::removeObject(Object * obj) {
  std::vector<int> vec = obj->gridPosition(); // get obj position
  removeGridObject(vec); // remove from the grid
  m_objects.at(obj->mesh()->name()).remove(obj);
}

void Level::setSkybox(const std::string &meshName) {
  Mesh *mesh = m_assets->mesh(meshName);
  if (!mesh)
    return;

  glm::vec3 pos(m_width / 2., 0, m_height / 2.);
  float size = m_width > m_height ? m_width : m_height; // the size is the maximum between the length and width of the level
  glm::vec3 scale(size + 10);
  m_skybox = new Skybox(mesh, pos, scale);
}

void Level::clear() {
  // Delete all objects
  m_objects.clear();
  m_character = nullptr;

  // Clear grid
  std::for_each(m_grid.begin(), m_grid.end(), [&](Eigen::SparseMatrix<Object*> &gridF) {
    gridF.setZero();
  });
}