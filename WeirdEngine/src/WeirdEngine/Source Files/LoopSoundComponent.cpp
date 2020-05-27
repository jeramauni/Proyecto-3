#include "LoopSoundComponent.h"
#include "ComponentFactory.h"

#include <AudioManager.h>

#include <iostream>

CREATE_REGISTER(LoopSound);

LoopSoundComponent::LoopSoundComponent(Container* e) {
	_name = "LoopSound";
	_parent = e;
	audioManager = _parent->getWEManager()->getAudioManager();
}

void LoopSoundComponent::Init(std::unordered_map<std::string, std::string>& param) {
	
}

void LoopSoundComponent::receive(Container* c, const msg::Message& msg) {
	switch (msg.type_) {
	case msg::SWITCH_COMP:
		_parent->activeComponent(_name);
		break;
	case msg::SCENE_OVER:
		_parent->getWEManager()->removeMouseListener(_name);
		break;
	case msg::SCENE_START:
		_parent->getWEManager()->removeMouseListener(_name);
		break;
	default:
		break;
	}
}
