#pragma once

namespace msg {

	// Nombres de los objetos del motor
	enum ObjectId {
		None,  	// special value indicating no object (or more precisely component)
		Broadcast,   // special value indicating all objects
		WEManager,
		Player,
		ColisionObject
		// ...
	};

	enum MessageType {
		GAME_START,
		GAME_OVER,
		SCENE_START,
		SCENE_OVER,
		MOVE,
		JUMP,
		CLOSE_WIN,
		COLISION,
		SWITCH_COMP
		//...
	};

	struct Message;

};