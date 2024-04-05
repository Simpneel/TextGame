#pragma once
#include "Room.h"
#include <Windows.h>
#include "Spell.h"

class Game {
public:
	bool keepGameRunning = true;
private:
	size_t x, y;

	String userInput;
	String outputs;
	String enemyStats;
	Room rooms[7][7];
	bool roomVisited[7][7] = {false};
	bool mapEnable = false;


	bool healDrop1Activate = false;
	bool healDrop2Activate = false;
	bool mapActivate = false;
	bool shortstaffActivate = false;
	bool desolateActivate = false;
	bool raActivate = false;
	bool exortActivate = false;

	Apple apple;
	Torch torch;
	Satchel satchel;
	HealDrop healdrop;
	Map map;
	Shortstaff shortstaff;
	Player player;
	Enemy enemy1;
	Enemy enemy2;
	Enemy enemy3;
	Enemy enemy4;
	Desolate desolate;
	Ra ra;
	Exort exort;

public:

	Game();
	void setEnemies(Enemy enemy1, Enemy enemy2, Enemy enemy3, Enemy enemy4);
	void setPlayer(Player player);
	void HUD();
	void Run();
};
