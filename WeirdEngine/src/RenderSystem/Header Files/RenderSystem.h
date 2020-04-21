#pragma once
#include <OgreString.h>
#include <map>

namespace Ogre {
	class OverlayManager;
	class Camera;
	class OverlayContainer;
	class Overlay;
	class OverlayElement;
	class TextAreaOverlayElement;
	class SceneManager;
	class Viewport;
	class SceneNode;
	class Entity;
	class Light;
	class ColourValue;
	class AnimationState;

	template <int dims, typename T> class Vector;
	typedef float Real;
	typedef Vector<3, Real> Vector3;
	class Quaternion;
};

class RenderSystem {

private:
	Ogre::SceneManager* mScnMgr = nullptr;
	Ogre::Camera* camera = nullptr;
	Ogre::String currentScene;

	// Contains Scene names and the SceneManager attached to
	std::map<Ogre::String, Ogre::SceneManager*> scenes;

	static RenderSystem* instance_;
	
	RenderSystem();
	~RenderSystem();

public:
	static bool initSingleton();
	static RenderSystem* getSingleton();

	// Adds an Ogre entity to the scene and returns the SceneNode containing it4
	Ogre::SceneNode* addOgreEntity(Ogre::String name);
	
	// Adds an empty node to the scene
	Ogre::SceneNode* addEmpty(Ogre::String name);

	// Returns the entity attached to the scene with the given name
	Ogre::Entity* getEntityByName(Ogre::String name);

	// Gets the root SceneNode
	inline Ogre::SceneNode* getRootNode();

	// Change the SceneManager
	inline void setSceneManager(Ogre::SceneManager* sm);

	enum LightTypes
	{
		/// Point light sources give off light equally in all directions, so require only position not direction
		LT_POINT = 0,
		/// Directional lights simulate parallel light beams from a distant source, hence have direction but no position
		LT_DIRECTIONAL = 1,
		/// Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
		LT_SPOTLIGHT = 2
	};

	// Creates a light and adds the lightNode to the scene
	Ogre::SceneNode* createLight(Ogre::String name, LightTypes type, Ogre::ColourValue diffuse, Ogre::ColourValue specular);

	// Sets the ambient light of the scene
	void setAmbientLight(Ogre::ColourValue color);

	// Sets the material to entity
	void setMaterial(Ogre::String entity, Ogre::String matName);

	// Sets the material to entity with entity access
	void setMaterial(Ogre::Entity* ent, Ogre::String matName);

	// Generates the different Resource Groups where take the materials
	void materialGeneration(Ogre::String nameOfResourceGroup);

	// Returns the camera to modify camera attributes 
	Ogre::Camera* getCamera();

	// Get the camera node to modify position, rotation, orientation ...
	Ogre::SceneNode* getCameraNode();

	// Get the viewport
	Ogre::Viewport* getViewport();

	// Adds a skybox to the current scene
	void setSkyBox(Ogre::String matName, Ogre::Real distance = 5000);

	// Sets up a camera in the actual rendering scene
	void addCamera();

	// Creates a new scene and adds it to the scenes dictionary with the given key
	void createScene(Ogre::String sceneName);

	// Sets the displayed scene to the scene given by parameter
	void setRenderingScene(Ogre::String sceneName);

	// Destroy all render entities
	void clearScene();

	// Gets the name of the displayed scene
	Ogre::String getCurrentScene();

	// Get the current SceneManager of the scene
	Ogre::SceneManager* getCurrentSceneManager() { return mScnMgr; };
};