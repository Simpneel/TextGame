#pragma once
#include "Room.h"
#include <Windows.h>
#include "Player.h"

class Game {
private:
	String userInput;
	Room rooms[7][7];
	bool roomVisited[7][7] = {false};

	size_t x, y;
	HealDrop healdrop;
	Map map;
	Shortstaff shortstaff;
	Player player;

public:
	Game();
	//~Game();
	void setPlayer(Player player);
	void HUD();
	void Run();
};
