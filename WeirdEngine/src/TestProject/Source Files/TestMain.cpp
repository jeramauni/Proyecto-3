// I will check for std::exception.
#include <exception>
#include <iostream>

#include "Game.h"

int main() {
	Game::instance.Init();
	//Game _g = Game();
	//_g.Init();

	//Bucle del juego
	while (Game::instance.update()) {}

	std::cout << "end of the program" << std::endl;

	return 0;
}
