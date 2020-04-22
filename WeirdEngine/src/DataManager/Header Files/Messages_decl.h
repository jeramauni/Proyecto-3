#pragma once

namespace msg {

	enum ObjectId {
		None,  	// special value indicating no object (or more precisely component)
		Broadcast,   // special value indicating all objects
		WEManager
		// ...
	};

	enum MessageType {
		GAME_START,
		GAME_OVER,
		ROUND_START,
		ROUND_OVER,
		PRUEBA,
		CLOSE_WIN
		//...
	};

	struct Message;

};