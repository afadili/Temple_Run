/**
 * \file main.cpp
 * \brief The main file of the game
 */

#include <iostream>
#include <Game/GameManager.hpp>

/**
 * \brief ============================== main ==================================
 */
int main(int argc, char **argv) {
  GameManager manager("test.json");
  return (EXIT_SUCCESS);
}