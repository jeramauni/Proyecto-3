#include "RenderSystem.h"
#include "WindowRenderer.h"

#include <Ogre.h>
#include <OgrePrerequisites.h>
#include <OgreResourceGroupManager.h>
#include <OgreMeshManager.h>
#include <OgreLogManager.h>
#include <OgreLog.h>
#include <OgreBuildSettings.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreCompositorManager.h>

RenderSystem* RenderSystem::instance_ = nullptr;

RenderSystem* RenderSystem::getSingleton()
{
	if (instance_ == nullptr) {
		instance_ = new RenderSystem();
	}

	return instance_;
}

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {

}

Ogre::SceneNode* RenderSystem::addOgreEntity(Ogre::String name)
{
	Ogre::Entity* mEntity = mScnMgr->createEntity(name, name + ".mesh");
	Ogre::SceneNode* mNode = mScnMgr->getRootSceneNode()->createChildSceneNode(name);
	
	mEntity->setMaterialName(name);

	mNode->attachObject(mEntity);

	// Mover el nodo para que lo vea la camara
	float lPositionOffset = float(1 * 2) - (float(1));
	lPositionOffset = lPositionOffset * 20;
	mNode->translate(lPositionOffset, lPositionOffset, -600.0f);
	mNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));

	return mNode;
}

Ogre::SceneNode* RenderSystem::addEmpty(Ogre::String name)
{
	return mScnMgr->getRootSceneNode()->createChildSceneNode(name);
}

Ogre::Entity* RenderSystem::getEntityByName(Ogre::String name)
{
	return mScnMgr->getEntity(name);
}

inline Ogre::SceneNode* RenderSystem::getRootSceneNode()
{
	return mScnMgr->getRootSceneNode();
}

inline Ogre::SceneManager* RenderSystem::getSceneManager()
{
	return mScnMgr;
}

inline void RenderSystem::setSceneManager(Ogre::SceneManager* sm)
{
	mScnMgr = sm;
}

Ogre::SceneNode* RenderSystem::createLight(Ogre::String name, LightTypes type, Ogre::ColourValue diffuse, Ogre::ColourValue specular)
{
	Ogre::Light* light = mScnMgr->createLight(name);
	light->setType(Ogre::Light::LightTypes(type));
	light->setDiffuseColour(diffuse);
	light->setSpecularColour(specular);

	Ogre::SceneNode* mLightNode = mScnMgr->getRootSceneNode()->createChildSceneNode(name);
	mLightNode->attachObject(light);

	return mLightNode;
}

void RenderSystem::setAmbientLight(Ogre::ColourValue color)
{
	mScnMgr->setAmbientLight(color);
}

void RenderSystem::setMaterial(Ogre::String entity, Ogre::String matName)
{
	getEntityByName(entity)->setMaterialName(matName);
}

void RenderSystem::setMaterial(Ogre::Entity* ent, Ogre::String matName)
{
	ent->setMaterialName(matName);
}

void RenderSystem::materialGeneration(Ogre::String nameOfResourceGroup)
{
	Ogre::MaterialManager& materialManager = Ogre::MaterialManager::getSingleton();

	Ogre::ResourceGroupManager& mRgMgr = Ogre::ResourceGroupManager::getSingleton();
	mRgMgr.createResourceGroup(nameOfResourceGroup);

	// Textures directory path
	Ogre::String textureDirectory = "resources/textures";
	mRgMgr.addResourceLocation(textureDirectory, "FileSystem", nameOfResourceGroup);

	// Initialise all resources
	mRgMgr.initialiseAllResourceGroups();

	// Load the desired resource group
	mRgMgr.loadResourceGroup(nameOfResourceGroup);
}

Ogre::Camera* RenderSystem::getCamera()
{
	return camera;
}

Ogre::SceneNode* RenderSystem::getCameraNode()
{
	return camera->getParentSceneNode();
}

Ogre::Viewport* RenderSystem::getViewport()
{
	return camera->getViewport();
}

void RenderSystem::setSkyBox(Ogre::String matName, Ogre::Real distance)
{
	mScnMgr->setSkyBox(true, matName, distance);
}

void RenderSystem::addCamera()
{
	Ogre::SceneManager* sm = WindowRenderer::getSingleton()->getRoot()->createSceneManager();
	setSceneManager(sm);

	float viewportWidth = 0.88f;
	float viewportHeight = 0.88f;
	float viewportLeft = (1.0f - viewportWidth) * 0.5f;
	float viewportTop = (1.0f - viewportHeight) * 0.5f;
	unsigned short mainViewportZOrder = 100;



	mScnMgr->createCamera("MainCam");
	Ogre::Viewport* vp = WindowRenderer::getSingleton()->getWin()->addViewport(mScnMgr->getCamera("MainCam"),
		mainViewportZOrder, viewportLeft, viewportTop, viewportWidth, viewportHeight);
	camera = mScnMgr->getCamera("MainCam");


	vp->setAutoUpdated(true);

	// Color for the viewPort
	vp->setBackgroundColour(Ogre::ColourValue(1, 0, 1));

	// I choose the visual ratio of the camera. To make it looks real, I want it the same as the viewport. 
	float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
	camera->setAspectRatio(ratio);


	//If (far/near)>2000 then you will likely get 'z fighting' issues.
	camera->setNearClipDistance(1.5f);
	camera->setFarClipDistance(3000.0f);

}

void RenderSystem::clearScene()
{
	mScnMgr->destroyAllEntities();
}

Ogre::String RenderSystem::getCurrentScene()
{
	return currentScene;
}

