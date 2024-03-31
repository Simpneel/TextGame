#include "Game.h"

Game::Game() {
	x = 3, y = 3;

	//Starting room
	rooms[3][3] = Room("Starting room", nullptr, 0);
	
	//North rooms
	rooms[3][0] = Room("North room 3", nullptr, 0);
	rooms[3][1] = Room("North room 2", new Item[1]{ Item("Healing Drop", "This item can restore HP") }, 1);
	rooms[3][2] = Room("North room 1", nullptr, 0);

	//South rooms
	rooms[3][4] = Room("South room 1", new Item[1]{ Item("Torch", "This item can light up a dark room",true) }, 1);
	rooms[3][5] = Room("South room 2", nullptr, 0);
	rooms[3][6] = Room("South room 3", nullptr, 0);
	//move north

	//West rooms
	rooms[2][3] = Room("West room 1", nullptr, 0);
	rooms[1][3] = Room("West room 2", new Item[1]{ Item("Map","This item can show you all explored rooms",true) }, 1);
	rooms[0][3] = Room("West room 3", nullptr, 0);

	//East rooms
	rooms[4][3] = Room("East room 1", new Item[1]{ Item("Healing Drop", "This item can restore HP",false) }, 1);
	rooms[5][3] = Room("East room 2", nullptr, 0);
	rooms[6][3] = Room("East room 3", new Item[1]{ Item("Shortstaff","This item increases the damage of attack based spells",false) }, 1);

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

void Game::Run() {
	roomVisited[3][3] = true;
	
	String getMap = map.Use(roomVisited, x, y);
	rooms[x][y].Description();

	userInput.ReadFromConsole();
	roomVisited[x][y] = true;
	HUD();
	String tempStorage = userInput;

	int tempLocStorage[2] = { x, y };

	int invalidRoomIndexes[32][2] = {						//Commenting out the rooms that allow me to skip through to the diagonal rooms
		{0,0},{1,0},{2,0},{4,0},{5,0},{6,0},
		{0,1},/*{2,1},{4,1},*/{6,1},	
		{0,2}/*,{1,2}*/,{2,2},{4,2},/*{5,2},*/{6,2},
		{0,4},/*{1,4},*/{2,4},{4,4},/*{5,4},*/{6,4},
		{0,5},/*{2,5},{4,5},*/{6,5},
		{0,6},{1,6},{2,6},{4,6},{5,6},{6,6} 
	};

	int diagonalRoomEntry[8][2] = {
		{2,1},{1,2},{4,1},{5,2},{1,4},{2,5},{4,5},{5,4}
	};

	userInput.ToLower();
	std::cout << std::endl;
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
		String::WriteInColor(11, "\t\t\n\nGAME PAUSED\n\n");
		system("color 87");
		system("pause");
		system("color 07");
		String::WriteInColor(11, "\t\t\n\nGAME UNPAUSED\n\n");
	}
	else if (userInput == "tp") {
		std::cin >> x;
		std::cin >> y;
	}
	else if (userInput == "show map") {
		getMap.WriteToConsole();
	}
	else {
		std::cout << "Invalid input! Please use the given commands only\n" << std::endl;
	}
	if (x > 6 || x < 0 || y>6 || y < 0) {
		std::cout << "\n Room doesn't exist! Try going a different way\n";
		x = tempLocStorage[0];
		y = tempLocStorage[1];
	}
	for (int i = 0; i < 32; i++) {
		if (x == invalidRoomIndexes[i][0] && y == invalidRoomIndexes[i][1]) {
			std::cout << "An unbreakable wall stops you from going that way. Try going a different way\n";
			x = tempLocStorage[0];
			y = tempLocStorage[1];
		}
		else if (x == diagonalRoomEntry[i][0] && y == diagonalRoomEntry[i][1]) {
			/*int tempStorage[2] = { diagonalRoomEntry[i][0], diagonalRoomEntry[i][1] };*/
			if ((x == 1 && y == 2) || (x == 2 && y == 1)) {
				x = 1; y = 1;
				String::WriteInColor(12, "YOU ENTERED AN ENEMY ROOM!\n");
				String::WriteInColor(12, "KILL THE ENEMY TO ESCAPE\n");
			}
			else if ((x == 4 && y == 1) || (x == 5 && y == 2)) {
				x = 5; y = 1;
				String::WriteInColor(12, "YOU ENTERED AN ENEMY ROOM!\n");
				String::WriteInColor(12, "KILL THE ENEMY TO ESCAPE\n");
			}
			else if ((x == 1 && y == 4) || (x == 2 && y == 5)) {
				x = 1; y = 5;
				String::WriteInColor(12, "YOU ENTERED AN ENEMY ROOM!\n");
				String::WriteInColor(12, "KILL THE ENEMY TO ESCAPE\n");
			}
			else {
				x = 5; y = 5;
				String::WriteInColor(12, "YOU ENTERED AN ENEMY ROOM!\n");
				String::WriteInColor(12, "KILL THE ENEMY TO ESCAPE\n");
			}
		}
	}
	
}

void Game::setPlayer(Player player) {
	this->player = player;
}

void Game::HUD() {
	system("cls");
	float HUDhealth = player.giveHealth();
	String::WriteInColor(10, HUDhealth);
	std::cout << "\t";
	String::WriteInColor(5, player.giveName());
	std::cout << std::endl; std::cout << std::endl;
	std::cout << "________--------_______";
	std::cout << std::endl;
	map.Use(roomVisited, x, y).WriteToConsole();
	std::cout << std::endl;
	std::cout << "________--------_______";
	std::cout << std::endl;
}
