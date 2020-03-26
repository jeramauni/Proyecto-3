// I will check for std::exception.
#include <exception>

//Podemos llamar a Ogre.h directamente e incluiriamos estas y mas
#include <Ogre.h>

#include "GameManager.h"
//TEST-------------------TEST-----------DATAMANAGER
#include<DataManager.h>
//TEST-------------------TEST-----------DATAMANAGER

#ifdef _DEBUG
int main()
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	try	{
		OgreEasy::OgreApp* OgreApp = new OgreEasy::OgreApp();
		OgreApp->AnOgreApplication();
		GameManager Game = GameManager(OgreApp);
		//TEST-------------------TEST-----------DATAMANAGER
		DataManager dM_;
		dM_.Load("map.json", "entities.json");
		//TEST-------------------TEST-----------DATAMANAGER
		while (Game.update())
		{
			//Bucle del juego
		}
		std::cout << "end of the program" << std::endl;
	}
	catch (Ogre::Exception & e)	{
		MWARNING("!!!!Ogre::Exception!!!!\n" << e.what());
	}
	catch (std::exception & e) {
		MWARNING("!!!!std::exception!!!!\n" << e.what());
	}

	OgreEasy::waitForUser();

	return 0;
}