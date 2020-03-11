#include <iostream>
#include <SDL.h>

#include "WindowRenderer.h"
#undef main

int main() {
	WindowRenderer* renderManager = WindowRenderer::getSingleton();

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