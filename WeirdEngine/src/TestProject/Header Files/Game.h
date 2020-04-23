#pragma once

class WEManager;

class Game {
public:
	Game();
	~Game();

	void Init();

	bool update();

private:
	WEManager* _weM;
};