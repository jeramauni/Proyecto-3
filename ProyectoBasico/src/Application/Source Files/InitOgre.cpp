//
// Copyright (c) 2007-2011, 'Madmarx' from the ogre3D forums (ogre3D.org).
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of its author nor the names of its contributors
//       may be used to endorse or promote products derived from this software
//       without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ------------------------------------------------------------------------------//
// ------------------------------------------------------------------------------//
#include "InitOgre.h"

// I will check for std::exception. If you don't know what exception/try/catch means, you should learn C++ first.
#include <exception>

// These are some files that we need to include to use Ogre3D. Note that you can at the beginnings use directly "Ogre.h", to include lots of commonly used classes.
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreFileSystemLayer.h>
//#include <OgreString.h>

#include "EasyDefines.h"

namespace OgreEasy {
	// the constructor uses the initialisation list to have a proper state.
	SimpleOgreInit::SimpleOgreInit()
		:mRoot(NULL), mWindow(NULL)
	{
		mFSLayer = new Ogre::FileSystemLayer("OgreApp");
	}

	// the destructor frees memory allocated by the class. 
	SimpleOgreInit::~SimpleOgreInit()
	{
		mWindow = NULL;
		mRoot.reset();// I was not obliged to do that...

		delete mFSLayer;
	}

	void SimpleOgreInit::initOgre()	{
		createRoot();
		//if (oneTimeConfig) setup();
		setup();
	}

	// Comprueba si ya hay una root iniciada y la resetea en caso afirmativo
	bool SimpleOgreInit::oneTimeConfig() {
		/*if (!mRoot->restoreConfig()) {
			return false;
		}
		else return true;*/
		return true;
	}

	void SimpleOgreInit::createRoot() {
		// This try/catch will catch potential exception launched by ogre or by my program.
		try {
			// 1 !!! Creamos la ROOT
			// This is the name of an optionnal textual configuration file for the rendersystem.
			Ogre::String lConfigFileName = "";

			// "lPluginsFileName" -> This is the name of an optional textual configuration file, which lists the available plugins.
			// "lLogFileName" -> This is the name of the log file. A log file is a file in which you can write things during the program execution.
			// Ogre use it to display general informations about the rendersystem.
			// You are not obliged to generate one, and ogre can even transmit the log data to you own class if you want.
			// Here we only ask the root to create the file.
#ifdef _DEBUG
			Ogre::String lPluginsFileName = "plugins_d.cfg";
			Ogre::String lLogFileName = "Ogre_d.log";
#else
			Ogre::String lPluginsFileName = "plugins.cfg";
			Ogre::String lLogFileName = "Ogre.log";
#endif

			// I create the root and I wrap it in an auto_ptr so that it will be automatically released.
			// Now I can even do "throw std::bad_alloc("bad alloc");", the program will release the root smoothly.
			// La root de Ogre inicializa automaticamente los plugins.
			mRoot = std::auto_ptr<Ogre::Root>(
				new Ogre::Root(lPluginsFileName, lConfigFileName, lLogFileName));

			// Then, we can select from the loaded plugins the unique RenderSystem we want to use.
			{
				// Hay que hacerlo manualmente ya que no tenemos OgreBites
				const Ogre::RenderSystemList& lRenderSystemList = mRoot->getAvailableRenderers();
				if (lRenderSystemList.size() == 0) {
					MWARNING("Sorry, no rendersystem was found.");
				}

				Ogre::RenderSystem* lRenderSystem = lRenderSystemList[0];
				mRoot->setRenderSystem(lRenderSystem);
			}
		}
		catch (Ogre::Exception & e) {
			MWARNING("!!!!Ogre::Exception!!!!" << e.what());
		}
		catch (std::exception & e) {
			MWARNING("!!!!std::exception!!!!" << e.what());
		}
	}

	void SimpleOgreInit::setup() {
		// Inicializamos la Root
		{
			// I can create a window automatically, but I won't do it.
			bool lCreateAWindowAutomatically = false;
			// name of the automatically generated window. empty for me.
			Ogre::String lWindowTitle = "";
			// custom capabilities of the rendersystem. It's a feature for advanced use.
			Ogre::String lCustomCapacities = "";
			mRoot->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);
		}

		// Creamos la ventana
		{
			Ogre::String lWindowTitle = "WeirdEngine Motors";
			unsigned int lSizeX = 800;
			unsigned int lSizeY = 600;
			//I don't want to use fullscreen during development.
			bool lFullscreen = false;
			// This is just an example of parameters that we can put. Check the API for more details.
			Ogre::NameValuePairList lParams;
			// fullscreen antialiasing. (check wikipedia if needed).
			lParams["FSAA"] = "0";
			// vertical synchronisation will prevent some image-tearing, but also
			// will provide smooth framerate in windowed mode.(check wikipedia if needed).
			lParams["vsync"] = "true";
			mWindow = mRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
		}

		// Cogemos los recursos que usaremos
		locateResources();
		loadResources();
	}

	void SimpleOgreInit::loadResources() {
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void SimpleOgreInit::locateResources() {
		// load resource paths from config file
		Ogre::ConfigFile cf;

#ifdef _DEBUG
		Ogre::String resourcesPath = "resources_d.cfg";
#else
		Ogre::String resourcesPath = "resources.cfg";
#endif
		if (Ogre::FileSystemLayer::fileExists(resourcesPath)) {
			cf.load(resourcesPath);
		}
		else {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				Ogre::FileSystemLayer::resolveBundlePath("resources/meshes"),
				"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		}

		Ogre::String sec, type, arch;
		// go through all specified resource groups
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
		// Coger los archivos segun la seccion donde se encuentran
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
			sec = seci->first;
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

			// go through all resource paths
			for (i = settings.begin(); i != settings.end(); i++) {
				type = i->first;
				arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
			}
		}

		//sec = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
		//sec = "Ninja";
		const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

		OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

		arch = genLocs.front().archive->getName();
		type = genLocs.front().archive->getType();

		// Add locations for supported shader languages
		/*
		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
			}
			else
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
			}

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
			}
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
		}

		mRTShaderLibPath = arch + "/RTShaderLib";
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
		}
		*/
	}
}