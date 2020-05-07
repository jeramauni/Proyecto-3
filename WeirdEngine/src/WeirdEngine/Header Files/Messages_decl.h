#pragma once

namespace msg {

	// Nombres de los objetos del motor
	enum ObjectId {
		None,  	// special value indicating no object (or more precisely component)
		Broadcast,   // special value indicating all objects
		WEManager, 
		Player
		// ...
	};

	enum MessageType {
		GAME_START,
		GAME_OVER,
		ROUND_START,
		ROUND_OVER,
		PRUEBA,
		CLOSE_WIN,
		//...
	};

	struct Message;

};