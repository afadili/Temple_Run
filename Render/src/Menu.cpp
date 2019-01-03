#include <Render/Menu.hpp>

Menu::Menu(){
      stateMenu = 0;
      stateLevel = 0;
      mode = 0;
      sommets[] = {
        Vertex2DColor(glm::vec2(-1, -1), glm::vec3(1, 0, 0), glm::vec2(0, 1)),
        Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1, 1)),
        Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0, 0)),
        Vertex2DColor(glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec2(1, 0)),
        Vertex2DColor(glm::vec2(1, -1), glm::vec3(0, 1, 0), glm::vec2(1, 1)),
        Vertex2DColor(glm::vec2(-1, 1), glm::vec3(0, 0, 1), glm::vec2(0, 0))};
}

void Menu::CreateTextureMenu(){

    if (mode == 0){
    FilePath menu = "data/assets/textures/menu.png";
    FilePath run = "data/assets/textures/run.png";
    FilePath replay = "data/assets/textures/replay.png";
    FilePath quit = "data/assets/textures/quit.png";

    textureMenu = Texture(menu);
    textureRun = Texture(run);
    textureReplay = Texture(replay);
    textureQuit = Texture(quit);

    }
    else if (mode == 1){
  FilePath Levelmenu = "data/assets/textures/Levelmenu.png";
  FilePath Level1menu = "data/assets/textures/Level1menu.png";
  FilePath Level2menu = "data/assets/textures/Level2menu.png";
  FilePath Level3menu = "data/assets/textures/Level3menu.png";

  textureLevelmenu = Texture(Levelmenu);
  textureLevel1menu = Texture(Level1menu);
  textureLevel2menu = Texture(Level2menu);
  textureLevel3menu = Texture(Level3menu);
    }
}


Menu::~Menu();


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
        textureMenu.bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        textureMenu.debind();
        }
        else if (stateMenu == 2)
        {
        textureRun.bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        textureRun.debind();
        }
        else if (stateMenu == 0)
        {
        textureQuit.bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        textureQuit.debind();
        }
        else if (stateMenu == 3)
        {
        textureReplay.bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        textureReplay.debind();
        }
    }

    if (mode == 1)
    {
        if (stateLevel == 1)
    {
      textureLevelmenu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureLevelmenu.debind();
    }
    else if (stateLevel == 2)
    {
      textureLevel1menu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureLevel1menu.debind();
    }
    else if (stateLevel == 0)
    {
      textureLevel2menu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureLevel2menu.debind();
    }
    else if (stateLevel == 3)
    {
      textureLevel3menu.bind();

      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);

      textureLevel3menu.debind();
    }
    }
}


