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

//Singleton
bool RenderSystem::initSingleton()
{
	if (instance_ == nullptr) {
		instance_ = new RenderSystem();

		return true;
	}
	return false;
}

RenderSystem* RenderSystem::getSingleton()
{
	return instance_;
}

// Constructora / Destructora
RenderSystem::RenderSystem() {
	WindowRenderer::initSingleton();
}

RenderSystem::~RenderSystem() {

}



//-------------------------------------------------
//Carga de materiales
void RenderSystem::materialGeneration(std::string nameOfResourceGroup)
{
	Ogre::MaterialManager& materialManager = Ogre::MaterialManager::getSingleton();

	Ogre::ResourceGroupManager& mRgMgr = Ogre::ResourceGroupManager::getSingleton();
	mRgMgr.createResourceGroup(nameOfResourceGroup);

	// Textures directory path
	std::string textureDirectory = "resources/textures";
	mRgMgr.addResourceLocation(textureDirectory, "FileSystem", nameOfResourceGroup);

	// Initialise all resources
	mRgMgr.initialiseAllResourceGroups();

	// Load the desired resource group
	mRgMgr.loadResourceGroup(nameOfResourceGroup);
}




//---------------------------ESCENA---------------------------------
// Crear una escena
void RenderSystem::createScene(std::string sceneName)
{
	Ogre::SceneManager* sMng = WindowRenderer::getSingleton()->getRoot()->createSceneManager();
	mScnMgr = sMng;

	addCamera("MainCam");

	scenes.erase(sceneName);
	scenes.insert({ sceneName, sMng });
}

// Indica cual es la escena a renderizar
void RenderSystem::setRenderingScene(std::string sceneName) {
	mScnMgr = scenes.find(sceneName)->second;

	camera = mScnMgr->getCamera("MainCam");

	currentScene = sceneName;
}

// Limpia las entidades de la escena activa actualmente
void RenderSystem::clearScene() {
	mScnMgr->destroyAllEntities();
}

Ogre::SceneNode* RenderSystem::createLight(std::string name, LightTypes type, Ogre::ColourValue diffuse, Ogre::ColourValue specular)
{
	Ogre::Light* light = mScnMgr->createLight(name);
	light->setType(Ogre::Light::LightTypes(type));
	light->setDiffuseColour(diffuse);
	light->setSpecularColour(specular);

	Ogre::SceneNode* mLightNode = mScnMgr->getRootSceneNode()->createChildSceneNode(name);
	mLightNode->attachObject(light);

	return mLightNode;
}

// Luz ambiente a una escena
void RenderSystem::setAmbientLight(Ogre::ColourValue color)
{
	mScnMgr->setAmbientLight(color);
}

void RenderSystem::setSkyBox(std::string matName, Ogre::Real distance)
{
	mScnMgr->setSkyBox(true, matName, distance);
}

std::string RenderSystem::getCurrentScene()
{
	return currentScene;
}
//----------------------------------------------






//------------------ENTIDADES-----------------
//Añadir una entidad a la escena que este renderizandose
Ogre::SceneNode* RenderSystem::addOgreEntity(std::string name, std::string mesh_name)
{
	Ogre::Entity* mEntity = mScnMgr->createEntity(name, mesh_name + ".mesh");
	Ogre::SceneNode* mNode = addEmpty(name);
	
	mEntity->setMaterialName(mesh_name);

	mNode->attachObject(mEntity);

	return mNode;
}

Ogre::SceneNode* RenderSystem::getSceneNode(std::string name)
{
	return getEntityByName(name)->getParentSceneNode();
}

//Coger una entidad de la escena
Ogre::Entity* RenderSystem::getEntityByName(std::string name) {
	return mScnMgr->getEntity(name);
}

// Devuelve la pos de una entidad de la escena
const Ogre::Vector3 RenderSystem::getEntityPos(std::string name) {
	return mScnMgr->getEntity(name)->getParentSceneNode()->getPosition();
}

// Da la pos a una entidad de la escena
void RenderSystem::setEntityPos(std::string name, Ogre::Vector3 &p) {
	getEntityByName(name)->getParentNode()->setPosition(p);
}

//Dar material a una entidad de la escena
void RenderSystem::setMaterial(std::string entity, std::string matName)
{
	getEntityByName(entity)->setMaterialName(matName);
}

//Dar un material a una entidad
void RenderSystem::setMaterial(Ogre::Entity* ent, std::string matName)
{
	ent->setMaterialName(matName);
}

// Crear un nodo vacio
Ogre::SceneNode* RenderSystem::addEmpty(std::string name)
{
	return mScnMgr->getRootSceneNode()->createChildSceneNode(name);
}

//------------------------------------------









//--------------------CAMARA--------------------------
//--Generales--
//Obtener la camara activa
Ogre::Camera* RenderSystem::getCamera() {
	return camera;
}

//Obtener el nodo de la camara activa
Ogre::SceneNode* RenderSystem::getCameraNode()
{
	//return camera->getParentNode();
	return camera->getParentSceneNode();
}

//Obtener el viewport de la camara activa
Ogre::Viewport* RenderSystem::getViewport()
{
	return camera->getViewport();
}

//Mover la camara principal de la escena
void RenderSystem::moveCam(std::string cameraName, Ogre::Real x, Ogre::Real y, Ogre::Real z) {
	mScnMgr->getCamera(cameraName)->getParentSceneNode()->setPosition(x, y, z);
}

//Hacer que la camara principal mire a un lugar en especifico
void RenderSystem::camLookAt(std::string cameraName, Ogre::Vector3 v) {
	mScnMgr->getCamera(cameraName)->getParentSceneNode()->lookAt(v, Ogre::Node::TS_WORLD);
}

void RenderSystem::rotateCam(std::string cameraName, Ogre::Quaternion q) {
	mScnMgr->getCamera(cameraName)->rotate(q);
}


//--------Especificos--------
//Añadir una camara a una escena
void RenderSystem::addCamera(std::string cameraName) {
	Ogre::Camera* mCamera = nullptr;
	mCamera = mScnMgr->createCamera(cameraName);

	Ogre::SceneNode* mCamNode = nullptr;
	mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode("n" + cameraName);
	mCamNode->attachObject(mCamera);

	mCamNode->setPosition(0, 0, 0);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	//If (far/near)>2000 then you will likely get 'z fighting' issues.
	mCamera->setNearClipDistance(3.0f);
	mCamera->setFarClipDistance(4000.0f);
}


//Añadir un vp a una camara con un color
void RenderSystem::addVpToCam(std::string cameraName, Ogre::ColourValue c) {
	float viewportWidth = 0.88f;
	float viewportHeight = 0.88f;
	float viewportLeft = (1.0f - viewportWidth) * 0.5f;
	float viewportTop = (1.0f - viewportHeight) * 0.5f;
	unsigned short mainViewportZOrder = 100;

	Ogre::Camera* camera = mScnMgr->getCamera(cameraName);

	Ogre::Viewport* vp = WindowRenderer::getSingleton()->getWin()->addViewport(camera,
		mainViewportZOrder, viewportLeft, viewportTop, viewportWidth, viewportHeight);

	vp->setAutoUpdated(true);

	// Color for the viewPort
	vp->setBackgroundColour(c);

	// I choose the visual ratio of the camera. To make it looks real, I want it the same as the viewport. 
	float ratio = Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight());
	camera->setAspectRatio(ratio);
}
//----------------------------------------------------





//----------------------------------------------------
inline Ogre::SceneNode* RenderSystem::getRootNode()
{
	return mScnMgr->getRootSceneNode();
}

inline void RenderSystem::setSceneManager(Ogre::SceneManager* sm)
{
	mScnMgr = sm;
}
//-------------------------------------------------