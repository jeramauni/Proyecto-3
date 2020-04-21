// I will check for std::exception.
#include <exception>
#include <iostream>
//Podemos llamar a Ogre.h directamente e incluiriamos estas y mas
#include <Ogre.h>
#include <EasyDefines.h>

#include "Game.h"

int main() {
	try {
		Game _g = Game();
		_g.Init();

		//Bucle del juego
		while (_g.update()) {}

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
