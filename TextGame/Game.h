#pragma once
#include "Room.h"
#include <Windows.h>
#include "Spell.h"

class Game {
private:
	String userInput;
	Room rooms[7][7];
	bool roomVisited[7][7] = {false};
	bool mapEnable = false;

	bool healDrop1Activate = false;
	bool healDrop2Activate = false;
	bool mapActivate = false;
	bool shortstaffActivate = false;

	size_t x, y;
	HealDrop healdrop;
	Map map;
	Shortstaff shortstaff;
	Player player;
	Player enemy;
	String outputs;
	Desolate desolate;

public:
	Game();
	void addEnemy(Player enemy, Room room);
	void setPlayer(Player player);
	void HUD();
	void Run();
};
