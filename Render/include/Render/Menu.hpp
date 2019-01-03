/**
 * \file Menu.hpp
 * \brief description : Declaration of the class "Menu"
 */

/*#ifndef __Menu__HPP
#define __Menu__HPP

#include <glimac/glm.hpp>
#include <vector>
#include <Render/Texture.hpp>
#include <glimac/FilePath.hpp>


struct Vertex2DColor
{
  Vertex2DColor();
  Vertex2DColor(const glm::vec2 &vecPos, const glm::vec3 &vecCol, const glm::vec2 &vecTex) : position(vecPos), color(vecCol), texCoords(vecTex){}; // constructeur

  glm::vec2 position;
  glm::vec2 texCoords;
  glm::vec3 color;
};

/**
 * \class Menu
 * \brief class defining a Menu and associated actions
 */

/*class Menu {
  private:
  unsigned int mode;
  Vertex2DColor sommets[];
  Texture textureMenu;
  Texture textureRun;
  Texture textureReplay;
  Texture textureQuit;
  Texture textureLevelmenu;
  Texture textureLevel1menu;
  Texture textureLevel2menu;
  Texture textureLevel3menu;
  unsigned int stateMenu;
  unsigned int stateLevel;

public:
  /**
   * \brief constructor of the menu by loading the textures
   */
  //Menu();

  /**
   * \brief constructor of the menu by loading the textures
   */
  //void CreateTextureMenu();

  /**
   * \brief destructor of the menu by releasing the memory space of the textures
   */
  //~Menu();

  /**
   * \brief method that read the events and manages it with the Menu display
   */
  //void EventManager();

  /**
   * \brief methode that draws the Menu and the Level Menu
   */
  //void drawMenu();

//};

//#endif