#pragma once

#include <OgreFrameListener.h>
#include <map>
#include <SDL.h>
#undef main

namespace Ogre {
	class RenderWindow;
	class RenderSystem;
	class Root;
	class Viewport;
	class SceneManager;
}

class WindowRenderer : public Ogre::FrameListener
{
private:
	//We want it singleton
	static WindowRenderer* instance_; 

	Ogre::Root* mRoot = nullptr; // ogre root
	Ogre::RenderWindow* mWindow = nullptr; // ogre window
	SDL_Window* sdlWin = nullptr; // window handled by SDL
	Ogre::RenderSystem* renderSystem = nullptr;

	// Contains Scene names and the SceneManager attached to
	std::map<Ogre::String, Ogre::SceneManager*> scenes;

	// The current SceneManager displaying the scene
	Ogre::SceneManager* currentSceneManager = nullptr;
	
	// private constructor because of singleton pattern
	WindowRenderer();
	~WindowRenderer();

	void initWindow();
	void createRoot();
	void setupWindow();
	void initializeResources();
	void setupResources();

protected:
	friend class RenderSystem;
	void _createScene(Ogre::String sceneName);
	
public:
	static WindowRenderer* getSingleton();
	void renderFrame(float t);
	bool handleEvents(const SDL_Event evt);

	// Called when the frame starts rendering
	virtual bool frameStarted(const Ogre::FrameEvent& evt) { return true; };

	// Called when the frame ends rendering
	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; };

	//Virtual methods, dont really need to be changed
	virtual void windowMoved(Ogre::RenderWindow* rw) {};
	virtual void windowResized(Ogre::RenderWindow* rw) {};
	virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; };
	virtual void windowClosed();
	virtual void windowFocusChange(Ogre::RenderWindow* rw) {};

	inline  Ogre::Root* getRoot() { return mRoot; };
	inline Ogre::RenderWindow* getWin() { return mWindow; };

	Ogre::SceneManager* getCurrentSceneManager();
};

