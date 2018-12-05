/**
 * \file main.cpp
 * \brief The main file of the game
 */

#include <iostream>
#include "Error/Error.hpp"

/**
 * \brief ============================== main ==================================
 */
int main(int argc, char **argv) {
  Error err("TEST ERROR !!! ", AT);
  std::cout << err.what() << std::endl;
  return (EXIT_SUCCESS);
}
