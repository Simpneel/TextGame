#include "Game.h"

Game::Game()
{
	x = 3, y = 4;
	rooms[3][4] = Room("South room 1", new Item[2]{ Item("Torch", "This is a torch"), Item("Healing Drop","This item can restore HP")}, 2);
	rooms[3][3] = Room("Starting room", nullptr, 0);
	userInput = "";
}

//Game::~Game()
//{
//}

void Game::Run()
{
	rooms[x][y].Description();
	userInput.ReadFromConsole();
	userInput.ToLower();
	if (userInput == "move south") {
		y ++;

	}
}
