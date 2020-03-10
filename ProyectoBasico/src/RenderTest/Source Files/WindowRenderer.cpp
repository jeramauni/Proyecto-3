#include "WindowRenderer.h"

#include <exception>

#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreFileSystemLayer.h>
#include <OgreSceneManager.h>

#include <SDL_video.h>
#include <SDL_syswm.h>
#include <SDL.h>

WindowRenderer* WindowRenderer::instance_ = nullptr;

WindowRenderer::WindowRenderer() : mRoot(0)
{
	initWindow();
}

void WindowRenderer::initWindow()
{
	createRoot();
	setupResources();
	mRoot->initialise(false);
	setupWindow();
	initializeResources();
	mRoot->addFrameListener(this);
}

void WindowRenderer::createRoot()
{
	try
	{
		Ogre::String configFileName = "";
#ifdef _DEBUG
		Ogre::String pluginsFileName = "plugins_d.cfg";
		Ogre::String logFileName = "Ogre_d.log";
#else
		Ogre::String pluginsFileName = "plugins.cfg";
		Ogre::String logFileName = "Ogre.log";
#endif

		mRoot = new Ogre::Root(pluginsFileName, configFileName, logFileName);

		// Asignar desde los plugins disponibles un sistema de renderizado
		const Ogre::RenderSystemList& lRenderSystemList = mRoot->getAvailableRenderers();
		
		renderSystem = lRenderSystemList[0];
		mRoot->setRenderSystem(renderSystem);
	}
	catch (Ogre::Exception & e) {
		//MWARNING("!!!!Ogre::Exception!!!!" << e.what());
	}
	catch (std::exception & e) {
		//MWARNING("!!!!std::exception!!!!" << e.what());
	}
}

void WindowRenderer::setupWindow()
{
	// Aqui se configura la ventana del juego
	Ogre::String winTitle = "WeirdEngine";
	unsigned int winWidth = 800;
	unsigned int winHeight = 600;

	Ogre::ConfigOptionMap renderOpts = mRoot->getRenderSystem()->getConfigOptions();
	// Parametros adicionales para la configuracion
	Ogre::NameValuePairList miscParams;
	// Full Screen Antialiasing
	miscParams["FSAA"] = renderOpts["FSAA"].currentValue;
	// Vertical Synchronisation
	miscParams["vsync"] = renderOpts["VSync"].currentValue;
	// Gamma level
	miscParams["gamma"] = renderOpts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_RESIZABLE;
	if (renderOpts["Full Screen"].currentValue == "Yes")flags = SDL_WINDOW_FULLSCREEN;

	sdlWin = SDL_CreateWindow(winTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, flags);
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(sdlWin, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	mWindow = mRoot->createRenderWindow(winTitle, winWidth, winHeight, false, &miscParams);
}

void WindowRenderer::initializeResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void WindowRenderer::setupResources()
{
}

WindowRenderer* WindowRenderer::getSingleton()
{
	if (instance_ == nullptr) {
		instance_ = new WindowRenderer();
	}

	return instance_;
}

void WindowRenderer::renderFrame(float t)
{
	mRoot->renderOneFrame();
}

bool WindowRenderer::handleEvents(const SDL_Event evt)
{
	bool handled = false;

	switch (evt.type)
	{
	case SDL_WINDOWEVENT:
		if (evt.window.windowID == SDL_GetWindowID(sdlWin)) {
			if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
				Ogre::RenderWindow* win = mWindow;
				win->windowMovedOrResized();
				//windowResized(win);
				handled = true;
			}
		}

		break;

	default:
		break;
	}
	return handled;
}
