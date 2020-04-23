#include "WEInput.h"

WEInput::WEInput() {

}

void WEInput::Init(std::unordered_map<std::string, std::string>& param) {

}

bool WEInput::keyPressed(const OIS::KeyEvent& ke) {
    switch (ke.key) {
    case OIS::KC_ESCAPE:
        //_owner->send(this, msg::Close_Win(msg::WEManager, msg::Broadcast));
        break;
    case OIS::KC_SPACE:
        //_owner->send(this, msg::Prueba(msg::WEManager, msg::Broadcast));
        break;
    default:
        break;
    }

    return true;
}

bool WEInput::keyReleased(const OIS::KeyEvent& ke) {



	return false;
}
