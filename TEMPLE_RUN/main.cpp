/**
 * \file main.cpp
 * \brief The main file of the game
 */

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <Game/GameManager.hpp>

/**
 * \brief ============================== main ==================================
 */

using namespace glimac;

// Nombre minimal de millisecondes separant le rendu de deux images
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char **argv) {
	// TEST GAME MANAGER
	GameManager manager("TEMPLE_RUN/assets.json");


	// Initialize SDL and open a window
	SDLWindowManager windowManager(800, 600, "I N F I N I T Y  R U N");

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if (GLEW_OK != glewInitError) {
	    std::cerr << glewGetErrorString(glewInitError) << std::endl;
	    return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	/*********************************
	 * HERE SHOULD COME THE INITIALIZATION CODE
	 *********************************/

	// Application loop:
	bool done = false;
	while (!done) {
	    Uint32 startTime = SDL_GetTicks();
	    // Event loop:
	    SDL_Event e;
	    while (windowManager.pollEvent(e)) {
	        if (e.type == SDL_QUIT) {
	            done = true; // Leave the loop after this iteration
	        }
	    }

	    /*********************************
	     * HERE SHOULD COME THE RENDERING CODE
	     *********************************/

	    // Update the display
	    windowManager.swapBuffers();
	    Uint32 elapsedTime = SDL_GetTicks() - startTime;
	    if (elapsedTime < FRAMERATE_MILLISECONDS) {
	        SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
	    }
	}

    return EXIT_SUCCESS;
}