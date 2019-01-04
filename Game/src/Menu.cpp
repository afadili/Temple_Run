#include <Game/Menu.hpp>

Menu::Menu(const AssetsManager *assets) : m_assets(assets) {
  m_stateMenu = 0;
  m_stateLevel = 0;
  m_mode = 0;
  m_sommets.push_back(Vertex2DColor(glm::vec2(-1, -1), glm::vec3(1, 0, 0), glm::vec2(0, 1)));
  m_sommets.push_back(Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1, 1)));
  m_sommets.push_back(Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0, 0)));
  m_sommets.push_back(Vertex2DColor(glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec2(1, 0)));
  m_sommets.push_back(Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1, 1)));
  m_sommets.push_back(Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0, 0)));

  m_texMenu["Menu"] = m_assets->texture("menutest");
  m_texMenu["Run"] = m_assets->texture("run");
  m_texMenu["Replay"] = m_assets->texture("replay");
  m_texMenu["Quit"] = m_assets->texture("quit");

  m_texMenu["LevelMenu"] = m_assets->texture("levelMenu");
  m_texMenu["Level1"] = m_assets->texture("level1");
  m_texMenu["Level2"] = m_assets->texture("level2");
  m_texMenu["Level3"] = m_assets->texture("level3");

}

Menu::~Menu() {
}

void Menu::EventManager(SDL_Event e) {
  if (m_mode == 0) {
    if (e.button.x > 261 && e.button.x < 538 && e.button.y > 239 && e.button.y < 310) {
      m_stateMenu = 2;
    } else if (e.button.x > 252 && e.button.x < 539 && e.button.y > 345 && e.button.y < 415) {
      m_stateMenu = 0;
    } else if (e.button.x > 243 && e.button.x < 532 && e.button.y > 450 && e.button.y < 520) {
      m_stateMenu = 3;
    } else {
      m_stateMenu = 1;
    }
  } else if (m_mode == 1) {
    if (e.button.x > 243 && e.button.x < 532 && e.button.y > 450 && e.button.y < 520) {
      std::cout << "Level 3 ! " << std::endl;
    } else if (e.button.x > 261 && e.button.x < 538 && e.button.y > 239 && e.button.y < 310) {
      std::cout << "Level 1 ! " << std::endl;
      m_stateLevel = 2;
    } else if (e.button.x > 252 && e.button.x < 539 && e.button.y > 345 && e.button.y < 415) {
      std::cout << "Level 2! " << std::endl;
    }
  }
}

void Menu::drawMenu() {
  if (m_mode == 0) {
    if (m_stateMenu == 1) {
      m_texMenu["Menu"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      m_texMenu["Menu"]->debind();
    } else if (m_stateMenu == 2) {
      m_texMenu["Run"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      m_texMenu["Run"]->debind();
    } else if (m_stateMenu == 0) {
      m_texMenu["Quit"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      m_texMenu["Quit"]->debind();
    } else if (m_stateMenu == 3) {
      m_texMenu["Replay"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      m_texMenu["Replay"]->debind();
    }
  }

  if (m_mode == 1) {
    if (m_stateLevel == 1) {
      m_texMenu["LevelMenu"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      m_texMenu["LevelMenu"]->debind();
    } else if (m_stateLevel == 2) {
      m_texMenu["Level1"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      m_texMenu["Level1"]->debind();
    } else if (m_stateLevel == 0) {
      m_texMenu["Level2"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      m_texMenu["Level2"]->debind();
    } else if (m_stateLevel == 3) {
      m_texMenu["Level3"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      m_texMenu["Level3"]->debind();
    }
  }
}