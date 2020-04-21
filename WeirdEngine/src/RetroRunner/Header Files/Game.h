#ifndef GAME_H
#define GAME_H

#pragma once

class GameManager;
class InputListener;

class Game {
public:
	Game();
	~Game();

	void Init();

	bool update();

private:
	GameManager* _gm;

	InputListener* input = NULL;
};
#endif