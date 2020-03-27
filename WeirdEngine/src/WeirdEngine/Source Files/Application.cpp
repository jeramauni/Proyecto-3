// I will check for std::exception.
#include <exception>
#include <iostream>
//Podemos llamar a Ogre.h directamente e incluiriamos estas y mas
#include <Ogre.h>

#include "GameManager.h"
//TEST-------------------TEST-----------DATAMANAGER
#include<DataManager.h>
//TEST-------------------TEST-----------DATAMANAGER

int main()

{
	try {
		GameManager Game = GameManager();
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