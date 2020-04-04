#pragma once

#include <vector>

//#include "GameObject.h" <- tpv

// you can replace these lines by corresponding
// includes once the classes are defined

//class Asteroid;
//class Bullet;

namespace msg {

	struct Message {
		Message(msg::MessageType type, msg::ObjectId sender) :
			size_(sizeof(Message)), type_(type), sender_(sender), destination_(msg::None) {
		}
		Message(msg::MessageType type, msg::ObjectId sender, msg::ObjectId destination, header_t_ size =
			sizeof(Message)) :
			size_(size),
			type_(type), sender_(sender), destination_(destination) {
		}
		msg::header_t_ size_;
		msg::MessageType type_;
		msg::ObjectId sender_;
		msg::ObjectId destination_;
	};
};