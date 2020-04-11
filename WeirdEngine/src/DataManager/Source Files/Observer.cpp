#include "Observer.h"

Observer::Observer() : id_(msg::None) {
}

Observer::~Observer() {
}

msg::ObjectId Observer::getId() {
	return id_;
}

void Observer::setId(msg::ObjectId id) {
	id_ = id;
}

bool Observer::receive(const void* senderObj, const msg::Message& msg)
{
	return false;
}
