#pragma once
#include "Room.h"
#include "Player.h"

class Game {
private:
	Room rooms[7][7];
	Player* player;

public:
	Game();
	~Game();
	void Run();
};