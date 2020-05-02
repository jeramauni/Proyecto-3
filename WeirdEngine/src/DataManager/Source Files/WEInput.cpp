#include "WEInput.h"

#include <iostream>

#include "Container.h"
#include "Messages_defs.h"

WEInput::WEInput(Container* c) : InputComponent(c){
    _listener = new WEInputListener(_owner);
}

void WEInput::Init(std::unordered_map<std::string, std::string>& param) {

}

WEInputListener* WEInput::getListener() {
    return _listener;
}

////-----------------------LISTENER-------------------------
WEInputListener::WEInputListener(Container* ow) {
    _owner = ow;
}

WEInputListener::~WEInputListener() {}

bool WEInputListener::keyPressed(const OIS::KeyEvent& ke) {
    switch (ke.key) {
    case OIS::KC_ESCAPE:
        _owner->globalSend(this, msg::Close_Win(msg::WEManager, msg::Broadcast));
        break;
    case OIS::KC_SPACE:
        std::cout << "Funciona\n";
        //_owner->localSend(this, msg::Prueba(msg::Player, msg::Broadcast));
        //_owner->send(this, msg::Prueba(msg::WEManager, msg::Broadcast));
        break;
    default:
        break;
    }

    return true;
}

bool WEInputListener::keyReleased(const OIS::KeyEvent& ke) {
    return false;
}