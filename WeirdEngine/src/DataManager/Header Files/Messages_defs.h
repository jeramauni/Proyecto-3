#pragma once

#include <vector>

//#include "GameObject.h" <- tpv
#include "EntityC.h"

// you can replace these lines by corresponding
// includes once the classes are defined

//class Asteroid;
//class Bullet;

namespace msg {

	struct Message {
		Message(msg::MessageType type, msg::ObjectId sender) :
			type_(type), sender_(sender), destination_(msg::None) {
		}
		Message(msg::MessageType type, msg::ObjectId sender, msg::ObjectId destination) :
			type_(type), sender_(sender), destination_(destination) {
		}
		msg::MessageType type_;
		msg::ObjectId sender_;
		msg::ObjectId destination_;
	};

	struct Prueba : public msg::Message{
		Prueba(msg::ObjectId sender, msg::ObjectId destination) :
			Message(msg::PRUEBA, sender, destination) {}
	};

	struct Close_Win : public msg::Message {
		Close_Win(msg::ObjectId sender, msg::ObjectId dest) :
			Message(msg::CLOSE_WIN, sender, dest) {}
	};
};