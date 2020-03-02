#include "GameManager.h"

#include "RenderComponent.h"
#include "EntityC.h"
#include "RenderUtilities.h"
#include "InitOgre.h"

GameManager::GameManager(OgreEasy::OgreApp * oa)
{
	ogreApp = oa;

	//--------------------------- LIGHT -----------------------------
	ogreApp->lightGeneration();

	//-------------------------- MATERIALS -------------------------------
	ogreApp->materialGeneration(" Mat");

	//--------------------------- SCENES ---------------------------
	EntityC* _util = new EntityC("ninja");
	menu->push(_util);

	_util = new EntityC("penguin");
	gamePlay->push(_util);

	changeScene(menu);
}

GameManager::~GameManager()
{
	escenas.empty();
}

bool GameManager::update()
{
	return ogreApp->RenderLoop();
}
void GameManager::changeScene(Scene * newScene)
{
	ogreApp->SceneCleaner();
	escenas.push(newScene);
	escenas.top()->render(ogreApp);
}