#pragma once

#include <vector>
#include "Utilities\Vector3.h"

class EntityC;

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

	struct Move : public msg::Message{
		Move(msg::ObjectId sender, msg::ObjectId destination, Vector3 dir) :
			Message(msg::MOVE, sender, destination), _dir(dir) {}
		Vector3 _dir;
	};

	struct Jump : public msg::Message {
		Jump(msg::ObjectId sender, msg::ObjectId destination, Vector3 dir) :
			Message(msg::JUMP, sender, destination), _dir(dir) {}
		Vector3 _dir;
	};

	struct Close_Win : public msg::Message {
		Close_Win(msg::ObjectId sender, msg::ObjectId dest) :
			Message(msg::CLOSE_WIN, sender, dest) {}
	};
};