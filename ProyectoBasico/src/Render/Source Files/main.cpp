// I will check for std::exception.
#include <exception>

// Includes necesarios
//#include <OgreRoot.h>
//#include <OgreRenderWindow.h>

//Podemos llamar a Ogre.h directamente e incluiriamos estas y mas
#include "WindowRenderer.h"
#include <SDL.h>


int main()
{
	WindowRenderer* renderManager= WindowRenderer::getSingleton();
	
	bool exit_ = false;
	
	while (!exit_) {
		SDL_Event evt;

		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) {
				exit_ = true;
			}

			renderManager->handleEvents(evt);
		}

		renderManager->renderFrame(10);
	}


	return 0;
}