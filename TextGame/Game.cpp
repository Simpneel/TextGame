#include "Game.h"

Game::Game() {
	x = 3, y = 3;

	//Starting room
	rooms[3][3] = Room("Starting room", nullptr, 0);
	
	//North rooms
	rooms[3][0] = Room("North room 3", nullptr, 0);
	rooms[3][1] = Room("North room 2", new Item[1]{ Item("Healing Drop", "This item can restore HP", healDrop1Activate) }, 1);
	rooms[3][2] = Room("North room 1", nullptr, 0);

	//South rooms
	rooms[3][4] = Room("South room 1", nullptr, 0);
	rooms[3][5] = Room("South room 2", nullptr, 0);
	rooms[3][6] = Room("South room 3", nullptr, 0);
	//move north

	//West rooms
	rooms[2][3] = Room("West room 1", nullptr, 0);
	rooms[1][3] = Room("West room 2", new Item[1]{ Item("Map","This item can show you all explored rooms", mapActivate) }, 1);
	rooms[0][3] = Room("West room 3", nullptr, 0);

	//East rooms
	rooms[4][3] = Room("East room 1", new Item[1]{ Item("Healing Drop", "This item can restore HP", healDrop2Activate) }, 1);
	rooms[5][3] = Room("East room 2", nullptr, 0);
	rooms[6][3] = Room("East room 3", new Item[1]{ Item("Shortstaff","This item increases the damage of attack based spells", shortstaffActivate) }, 1);

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
	outputs.Replace(outputs, "");
	roomVisited[3][3] = true;

	rooms[x][y].Description();

	userInput.ReadFromConsole();
	
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
		String::WriteInColor(11, "\n\n\t\tGAME PAUSED\n\n");
		system("color 87");
		system("pause");
		system("color 07");
		outputs.Append("\t\t\n\nGAME UNPAUSED\n\n");
	}
	else if (userInput == "tp") {
		std::cin >> x;
		std::cin >> y;
	}
	else if (userInput == "show map" && mapActivate == true) {
		mapEnable = true;
	}
	else if (userInput == "hide map") {
		mapEnable = false;
	}
	else if (userInput == "find item") {
		String::WriteInColor(91, "Enter item name to find\n");
		String tempInput;
		tempInput.ReadFromConsole();
		if (player.FindItem(tempInput) == true) {
			outputs.Append("You have this item in your inventory!\n");
		}
		else {
			outputs.Append("You don't have this item.\n");
		}
	}
	else if (userInput == "find spell") {
		String::WriteInColor(44, "Enter spell name to find\n");
		String tempInput;
		tempInput.ReadFromConsole();
		if (player.FindSpell(tempInput) == true) {
			outputs.Append("You have this spell in your spellbook!\n");
		}
		else {
			outputs.Append("You do not have this spell in your spellbook\n");
		}
	}
	else if (userInput == "attack") {

	}
	else if (userInput == "cast spell") {
		outputs.Append("Enter the spell you wish to cast\n");
		String tempInput;
		tempInput.ToLower();
		tempInput.ReadFromConsole();
		if (player.FindSpell(tempInput) == true) {
			if (tempInput == "desolate") {
				desolate.Cast(enemy);
			}
			else if (tempInput == "exort") {

			}
			else if (tempInput == "ra") {

			}
		}
	}
	else if (userInput == "command list") {
		outputs.Append("Here is a list of commands you can use:\n(p.s) capitalisation does not matter with any of these commands\n\n");
		outputs.Append("MOVE NORTH- Makes your player move to the room north of you\n");
		outputs.Append("MOVE SOUTH- Makes your player move to the room south of you\n");
		outputs.Append("MOVE WEST- Makes your player move to the room west of you\n");
		outputs.Append("MOVE EAST- Makes your player move to the room east of you\n");
		outputs.Append("PAUSE GAME\n");
		outputs.Append("FIND ITEM/SPELL- Prompts you to type an item/spell name in and check if it is available to you\n");
		outputs.Append("ATTACK- Attacks enemy using your base damage\n");
		outputs.Append("CAST SPELL- Prompts you to type a spell name in and use it against an enemy\n");
		if (healDrop1Activate || healDrop2Activate) {
			outputs.Append("HEAL- Heals you for half of your max hp\n\tConsumes one healing drop on use\n");
		}
		if (mapActivate == true) {
			outputs.Append("SHOW MAP- Opens the map and shows you all explored rooms\n");
			outputs.Append("HIDE MAP- Hides the map from your screen\n");
		}
	}
	else {
		outputs.Append("Invalid input! Please use the given commands only\n\n");
	}

	if (x > 6 || x < 0 || y>6 || y < 0) {
		std::cout << "\n Room doesn't exist! Try going a different way\n";
		x = tempLocStorage[0];
		y = tempLocStorage[1];
	}

	for (int i = 0; i < 32; i++) {
		if (x == invalidRoomIndexes[i][0] && y == invalidRoomIndexes[i][1]) {
			outputs.Append("An unbreakable wall stops you from going that way. Try going a different way\n");
			x = tempLocStorage[0];
			y = tempLocStorage[1];
		}
		else if (x == diagonalRoomEntry[i][0] && y == diagonalRoomEntry[i][1]) {
			/*int tempStorage[2] = { diagonalRoomEntry[i][0], diagonalRoomEntry[i][1] };*/
			if ((x == 1 && y == 2) || (x == 2 && y == 1)) {
				x = 1; y = 1;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				system("pause");
			}
			else if ((x == 4 && y == 1) || (x == 5 && y == 2)) {
				x = 5; y = 1;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				system("pause");
			}
			else if ((x == 1 && y == 4) || (x == 2 && y == 5)) {
				x = 1; y = 5;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				system("pause");
			}
			else {
				x = 5; y = 5;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				system("pause");
			}
		}
	}

	if (x == 3 && y == 1) {
		if (healDrop1Activate != true) {
			healDrop1Activate = true;
			outputs.Append("You have obtained two healing drops!\n");
			player.addItem("healing drop");
		}
	}
	if (x == 1 && y == 3) {
		if (mapActivate != true) {
			mapActivate = true;
			outputs.Append("You have obtained a map!\nThis item will show you a map of all rooms that you have visited.\nType \"show map\" to make it visible & \"hide map\" to hide it.\n");
			player.addItem("map");
		}
	}
	if (x == 4 && y == 3) {
		if (healDrop2Activate != true) {
			healDrop2Activate = true;
			outputs.Append("You have obtained two healing drops!\n");
			player.addItem("healing drop");
		}
	}
	if (x == 6 && y == 3) {
		if (shortstaffActivate != true) {
			shortstaffActivate = true;
			outputs.Append("You have obtained a shortstaff!\nThis item equips automatically and increases your spell damage!\n");
			player.addItem("shortstaff");
			player.dmgBuff(shortstaff);
		}
	}

	roomVisited[x][y] = true;
	HUD();
}

void Game::setPlayer(Player player) {
	this->player = player;
}

void Game::addEnemy(Player enemy, Room room) {
	
}

void Game::HUD() {
	system("cls");
	float HUDhealth = player.giveHealth();
	String::WriteInColor(10, "~~~~~~~~");
	std::cout << "\t";
	String::WriteInColor(5, " ~~~~~~~~\n");

	std::cout << "     ";
	String::WriteInColor(10, HUDhealth);
	String::WriteInColor(10, " | ");

	std::cout << "\t";

	String::WriteInColor(5, "| ");
	String::WriteInColor(5, player.giveName());
	std::cout << "\n";
	String::WriteInColor(10, "~~~~~~~~");
	std::cout << "\t";
	String::WriteInColor(5, " ~~~~~~~~\n");

	String::WriteInColor(12, "\n______________________________");

	std::cout << std::endl; std::cout << std::endl;
	std::cout << "________--------_______";
	std::cout << std::endl;
	if (mapEnable == true) {
		map.Use(roomVisited, x, y).WriteToConsole();
	}
	std::cout << std::endl;
	std::cout << "________--------_______";
	std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
	String::WriteInColor(8, "type \"command list\" to see all available inputs");
	outputs.Prepend("\t\t\t");
	outputs.WriteInColor(79, outputs);
}
