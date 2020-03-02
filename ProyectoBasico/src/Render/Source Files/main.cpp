// I will check for std::exception.
#include <exception>

// Includes necesarios
//#include <OgreRoot.h>
//#include <OgreRenderWindow.h>

//Podemos llamar a Ogre.h directamente e incluiriamos estas y mas
#include <Ogre.h>
#include "OgreApp.h"
#include "WindowRenderer.h"
#include <Application2.h>
#include <SDL.h>


#ifdef _DEBUG
int main()
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	/*
	try	{
		OgreEasy::OgreApp OgreApp;
		OgreApp.AnOgreApplication();
		std::cout << "end of the program" << std::endl;
	}
	catch (Ogre::Exception & e)	{
		MWARNING("!!!!Ogre::Exception!!!!\n" << e.what());
	}
	catch (std::exception & e) {
		MWARNING("!!!!std::exception!!!!\n" << e.what());
	}

	OgreEasy::waitForUser();
	*/
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