#pragma once

class WEManager;

class Game {
public:
	Game();
	~Game();

	void Init();
	bool update();

	static Game instance;
private:
	WEManager* _weM;

	void GenerateMainScene();
	void GenerateMenuScene();
	void GeneratePauseScene();

	//Eventos
	static void EventEnd();
	static void EventStart();
};