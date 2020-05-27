#pragma once
#include "Component.h"
#include <OgreVector.h>

#include "Utilities\Vector3.h"

class Container;
class AudioManager;

class LoopSoundComponent : public Component {
public:
	LoopSoundComponent(Container* e) ;
	~LoopSoundComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg);

private:
	AudioManager* audioManager;
};