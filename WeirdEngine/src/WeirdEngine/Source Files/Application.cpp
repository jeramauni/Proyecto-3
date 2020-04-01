// I will check for std::exception.
#include <exception>
#include <iostream>
//Podemos llamar a Ogre.h directamente e incluiriamos estas y mas
#include <Ogre.h>
#include <EasyDefines.h>

#include "GameManager.h"

int main()

{
	try {
		GameManager Game = GameManager();
		Game.Init();
		while (Game.update())
		{
			//Bucle del juego
		}
		std::cout << "end of the program" << std::endl;
	}
	catch (Ogre::Exception & e) {
		MWARNING("!!!!Ogre::Exception!!!!\n" << e.what());
	}
	catch (std::exception & e) {
		MWARNING("!!!!std::exception!!!!\n" << e.what());
	}

	return 0;
}