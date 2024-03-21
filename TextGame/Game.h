#pragma once
#include "Room.h"
#include <Windows.h>
/*#include "Player.h"*/

class Game {
private:
	String userInput;
	Room rooms[7][7];

	size_t x, y;
	//Player* player;

public:
	Game();
	//~Game();
	void Run();
};