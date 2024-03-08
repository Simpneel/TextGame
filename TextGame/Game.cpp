#include "Game.h"

Game::Game()
{
	x = 3, y = 3;

	//Starting room
	rooms[3][3] = Room("Starting room", nullptr, 0);
	
	//North rooms
	rooms[3][0] = Room("North room 3", nullptr, 0);
	rooms[3][1] = Room("North room 2", new Item[1]{ Item("Healing Drop", "This item can restore HP") }, 1);
	rooms[3][2] = Room("North room 1", nullptr, 0);

	//South rooms
	rooms[3][4] = Room("South room 1", new Item[1]{ Item("Torch", "This item can light up a dark room") }, 1);
	rooms[3][5] = Room("South room 2", nullptr, 0);
	rooms[3][6] = Room("South room 3", nullptr, 0);
	//move north

	//West rooms
	rooms[2][3] = Room("West room 1", nullptr, 0);
	rooms[1][3] = Room("West room 2", new Item[1]{ Item("Map","This item can show you all explored rooms") }, 1);
	rooms[0][3] = Room("West room 3", nullptr, 0);

	//East rooms
	rooms[4][3] = Room("East room 1", new Item[1]{ Item("Healing Drop", "This item can restore HP") }, 1);
	rooms[5][3] = Room("East room 2", nullptr, 0);
	rooms[6][3] = Room("East room 2", new Item[1]{ Item("Shortstaff","This item increases the damage of attack based spells") }, 1);

	//Fight rooms
	rooms[1][1] = Room("North West room", nullptr, 0);
	rooms[5][1] = Room("North East room", nullptr, 0);
	rooms[5][5] = Room("South East room", nullptr, 0);
	rooms[1][5] = Room("South West room", nullptr, 0);
	userInput = "";
}

//Game::~Game()
//{
//}

void Game::Run()
{
	rooms[x][y].Description();
	userInput.ReadFromConsole();
	String tempStorage = userInput;

	int tempLocStorage[2] = { x, y };

	int invalidRoomIndexes[32][2] = {
		{0,0},{1,0},{2,0},{4,0},{5,0},{6,0},
		{0,1},{2,1},{4,1},{6,1}	};

	userInput.ToLower();
	if (userInput == "move south") {
		y ++;
	}
	else if (userInput == "move north") {
		y--;
	}
	else if (userInput == "move west") {
		x--;
	}
	else if (userInput == "move east") {
		x++;
	}
	else if (userInput == "pause game") {
		std::cout << "\t\t\nGame paused\n";
		system("pause");
		std::cout << "\t\t\nGame unpaused\n";
	}
	else {
		std::cout << "Invalid input! Please use the given commands only" << std::endl;
	}
	if (x > 6 || x < 0 || y>6 || y < 0) {
		std::cout << "\n Room doesn't exist! Try going a different way";
		x = tempLocStorage[0];
		y = tempLocStorage[1];
	}
}
