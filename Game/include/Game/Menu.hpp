/**
 * \file Menu.hpp
 * \brief description : Declaration of the class "Menu"
 */

#ifndef __Menu__HPP
#define __Menu__HPP

#include <glimac/glm.hpp>
#include <vector>
#include <Render/Texture.hpp>
#include <glimac/FilePath.hpp>
#include <map>
#include <string>
#include <Game/AssetsManager.hpp>
#include <Render/Texture.hpp>

struct Vertex2DColor {
  Vertex2DColor();

  Vertex2DColor(const glm::vec2 &vecPos, const glm::vec3 &vecCol, const glm::vec2 &vecTex) : position(vecPos), color(vecCol), texCoords(vecTex) {
  }; // constructeur

  glm::vec2 position;
  glm::vec2 texCoords;
  glm::vec3 color;
};

/**
 * \class Menu
 * \brief class defining a Menu and associated actions
 */

class Menu {
private:
  std::vector<Vertex2DColor> m_sommets;
  std::map<std::string, Texture*> m_texMenu;
  const AssetsManager *m_assets;
  unsigned int m_mode;
  unsigned int m_stateMenu;
  unsigned int m_stateLevel;

private:
  Menu() = default;

public:
  /**
   * \brief constructor of the menu by loading the textures
   */
  Menu(const AssetsManager *assets);

  /**
   * \brief destructor of the menu by releasing the memory space of the textures
   */
  ~Menu();

  /**
   * \brief method that read the events and manages it with the Menu display
   */
  void EventManager(SDL_Event e);

  /**
   * \brief methode that draws the Menu and the Level Menu
   */
  void drawMenu();

};

#endif
