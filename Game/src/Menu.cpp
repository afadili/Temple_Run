#include <Game/Menu.hpp>

Menu::Menu(){
      stateMenu = 0;
      stateLevel = 0;
      mode = 0;
      sommets.push_back(Vertex2DColor(glm::vec2(-1, -1), glm::vec3(1, 0, 0), glm::vec2(0, 1)));
      sommets.push_back(Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1, 1)));
      sommets.push_back(Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0, 0)));
      sommets.push_back(Vertex2DColor(glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec2(1, 0)));
      sommets.push_back(Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1, 1)));
      sommets.push_back(Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0, 0)));

             std::cout << "Menuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu" << std::endl;



       texMenu["Menu"] = m_assetsMenu->texture("menutest");
        texMenu["Run"] = m_assetsMenu->texture("run");
        texMenu["Replay"] = m_assetsMenu->texture("replay");
        texMenu["Quit"] = m_assetsMenu->texture("quit");

        texMenu["LevelMenu"] = m_assetsMenu->texture("levelMenu");
        texMenu["Level1"] = m_assetsMenu->texture("level1");
        texMenu["Level2"] = m_assetsMenu->texture("level2");
        texMenu["Level3"] = m_assetsMenu->texture("level3");

  if (m_assetsMenu != nullptr)
  {
    std::cout << "pointeur pas nul ! " << std::endl;
  } 
  std::cout << "pointeur nul !!!!!!!!!!!!!!!!!!!!" << std::endl;
}


Menu::~Menu(){}


void Menu::EventManager(SDL_Event e){
    if (mode == 0)
    {
        if (e.button.x > 261 && e.button.x < 538 && e.button.y > 239 && e.button.y < 310)
      {
        stateMenu = 2;
      }
      else if (e.button.x > 252 && e.button.x < 539 && e.button.y > 345 && e.button.y < 415)
      {
        stateMenu = 0;
      }
      else if (e.button.x > 243 && e.button.x < 532 && e.button.y > 450 && e.button.y < 520)
      {
        stateMenu = 3;
      }
      else
      {
        stateMenu = 1;
      }
    }

    else if (mode == 1){
        if (e.button.x > 243 && e.button.x < 532 && e.button.y > 450 && e.button.y < 520)
          {
            std::cout << "Level 3 ! " << std::endl;
          }
          else if (e.button.x > 261 && e.button.x < 538 && e.button.y > 239 && e.button.y < 310)
          {
            std::cout << "Level 1 ! " << std::endl;
            stateLevel = 2;
          }
          else if (e.button.x > 252 && e.button.x < 539 && e.button.y > 345 && e.button.y < 415)
          {
            std::cout << "Level 2! " << std::endl;
          }
    }
}

void Menu::drawMenu(){
    if (mode == 0)
    {
        if (stateMenu == 1)
        {
        texMenu["Menu"]->bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        texMenu["Menu"]->debind();
        }
        else if (stateMenu == 2)
        {
        texMenu["Run"]->bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        texMenu["Run"]->debind();
        }
        else if (stateMenu == 0)
        {
        texMenu["Quit"]->bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        texMenu["Quit"]->debind();
        }
        else if (stateMenu == 3)
        {
        texMenu["Replay"]->bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        texMenu["Replay"]->debind();
        }
    }

    if (mode == 1)
    {
        if (stateLevel == 1)
    {
      texMenu["LevelMenu"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      texMenu["LevelMenu"]->debind();
    }
    else if (stateLevel == 2)
    {
      texMenu["Level1"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      texMenu["Level1"]->debind();
    }
    else if (stateLevel == 0)
    {
      texMenu["Level2"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      texMenu["Level2"]->debind();
    }
    else if (stateLevel == 3)
    {
      texMenu["Level3"]->bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      texMenu["Level3"]->debind();
    }
    }
}