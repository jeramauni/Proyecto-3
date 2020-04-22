#ifndef GAME_H
#define GAME_H

#pragma once

class WEManager;
class InputListener;

class Game {
public:
	Game();
	~Game();

	void Init();

	bool update();

private:
	WEManager* _weM;

	InputListener* input = NULL;
};
#endif