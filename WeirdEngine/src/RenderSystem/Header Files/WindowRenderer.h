#pragma once

#include <OgreFrameListener.h>
#include <string>
#include <SDL.h>

namespace Ogre {
	class RenderWindow;
	class RenderSystem;
	class Root;
	class FileSystemLayer;
}

class WindowRenderer : public Ogre::FrameListener
{
private:
	//We want it singleton
	static WindowRenderer* instance_; 

	Ogre::Root* mRoot = nullptr;
	Ogre::RenderWindow* mWindow = nullptr;
	SDL_Window* sdlWin = nullptr;
	Ogre::RenderSystem* renderSystem = nullptr;
	
	// private constructor because of singleton pattern
	WindowRenderer();

	void initWindow();
	void createRoot();
	void setupWindow();
	void initializeResources();
	void setupResources();
public:
	static WindowRenderer* getSingleton();
	void renderFrame(float t);
	bool handleEvents(const SDL_Event evt);

	inline  Ogre::Root* getRoot() { return mRoot; };

};

