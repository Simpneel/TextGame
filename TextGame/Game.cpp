#include "Game.h"

Game::Game() {
	x = 3, y = 3;

	//Starting room
	rooms[3][3] = Room("Starting room", nullptr, 0);
	
	//North rooms
	rooms[3][0] = Room("North room 3", exort);
	rooms[3][1] = Room("North room 2", new Item[1]{ Item("Healing Drop", "This item can restore HP", healDrop1Activate) }, 1);
	rooms[3][2] = Room("North room 1", nullptr, 0);

	//South rooms
	rooms[3][4] = Room("South room 1", desolate);
	rooms[3][5] = Room("South room 2", nullptr, 0);
	rooms[3][6] = Room("South room 3", ra);
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
	rooms[1][1] = Room("North West room");
	rooms[5][1] = Room("North East room");
	rooms[5][5] = Room("South East room");
	rooms[1][5] = Room("South West room");
	userInput = "";
	enemyStats = "";
}

//Game::~Game()
//{
//}

void Game::Run() {
	outputs.Replace(outputs, "");
	enemyStats.Replace(enemyStats, "");
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
	else if (userInput == "exit game") {
		String::WriteInColor(4, "Are you sure you want to give up?\nNo progress will be saved\n\nType YES to exit and NO to continue\n");
		String seeIfPlayerIsALoser;
		seeIfPlayerIsALoser.ReadFromConsole().ToLower();
		if (seeIfPlayerIsALoser.EqualTo("yes")) {
			keepGameRunning = false;
		}
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
	else if (userInput == "heal") {
		if (healdrop.getCount() > 0) {
			player.setHealth(healdrop.Use(player.giveHealth()));
			healdrop.setCount(healdrop.getCount() - 1);
			outputs.Append("\t\t\tOne healing drop consumed!\n");
		}
		else if (healDrop1Activate != true && healDrop2Activate != true) {
			outputs.Append("You need to first find a healing drop to use this command, you noob.\n");
		}
		else {
			outputs.Append("You don't have any healing drops left. Good luck with no heals you tryhard.\n");
		}
	}
	else if (userInput == "find item") {
		String::WriteInColor(13, "Enter item name to find\n");
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
		String::WriteInColor(13, "Enter spell name to find\n");
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
		if ((x == 1 || x == 5) && (y == 1 || y == 5)) {
			if (x == 1 && y == 1) {
				outputs.Append(enemy1.giveName());
				enemy1.takeDamage(player.giveDamage());
				outputs.Append(" was hit!\n");
				enemyStats.Append(enemy1.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy1.giveHealth());
			}
			else if (x == 5 && y == 1) {
				outputs.Append(enemy2.giveName());
				enemy2.takeDamage(player.giveDamage());
				outputs.Append(" was hit!\n");
				enemyStats.Append(enemy2.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy2.giveHealth());
			}
			else if (x == 5 && y == 5) {
				outputs.Append(enemy3.giveName());
				enemy3.takeDamage(player.giveDamage());
				outputs.Append(" was hit!\n");
				enemyStats.Append(enemy3.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy3.giveHealth());
			}
			else {
				outputs.Append(enemy4.giveName());
				enemy4.takeDamage(player.giveDamage());
				outputs.Append(" was hit!\n");
				enemyStats.Append(enemy4.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy4.giveHealth());
			}
		}
		else {
			outputs.Append("There is no enemy here to attack, what are you doing?\n");
		}
	}
	else if (userInput == "cast spell") {
		String::WriteInColor(111,"\nEnter one of your spell names to cast\n");
		String tempInput;
		tempInput.ReadFromConsole();
		tempInput.ToLower();
		if (/*player.FindSpell(tempInput) == */true) {
			if (tempInput == "desolate" && desolateActivate == true) {
				if (x == 1 && y == 1) {
					outputs.Append(enemy1.giveName());
					outputs.Append(" was hit!\n");
					desolate.Cast(enemy1);
					enemyStats.Append(enemy1.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy1.giveHealth());
				}
				else if (x == 5 && y == 1) {
					outputs.Append(enemy2.giveName());
					outputs.Append(" was hit!\n");
					desolate.Cast(enemy2);
					enemyStats.Append(enemy2.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy2.giveHealth());
				}
				else if (x == 5 && y == 5) {
					outputs.Append(enemy3.giveName());
					outputs.Append(" was hit!\n");
					desolate.Cast(enemy3);
					enemyStats.Append(enemy3.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy3.giveHealth());
				}
				else if (x == 1 && y == 5) {
					outputs.Append(enemy4.giveName());
					outputs.Append(" was hit!\n");
					desolate.Cast(enemy4);
					enemyStats.Append(enemy4.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy4.giveHealth());
				}
				else {
					outputs.Append("Who are you casting this on?\n\t\t\tNo enemies nearby\n");
				}
			}
			else if (tempInput == "exort" && exortActivate == true) {
				if (x == 1 && y == 1) {
					outputs.Append(enemy1.giveName());
					outputs.Append(" was hit!\n");
					exort.Cast(enemy1);
					enemyStats.Append(enemy1.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy1.giveHealth());
				}
				else if (x == 5 && y == 1) {
					outputs.Append(enemy2.giveName());
					outputs.Append(" was hit!\n");
					exort.Cast(enemy2);
					enemyStats.Append(enemy2.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy2.giveHealth());
				}
				else if (x == 5 && y == 5) {
					outputs.Append(enemy3.giveName());
					outputs.Append(" was hit!\n");
					exort.Cast(enemy3);
					enemyStats.Append(enemy3.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy3.giveHealth());
				}
				else if (x == 1 && y == 5){
					outputs.Append(enemy4.giveName());
					outputs.Append(" was hit!\n");
					exort.Cast(enemy4);
					enemyStats.Append(enemy4.giveName()); enemyStats.Append(" | "); enemyStats.Append(enemy4.giveHealth());
				}
				else {
					outputs.Append("Who are you casting this on?\n\t\t\tNo enemies nearby\n");
				}
			}
			else if (tempInput == "ra" && raActivate == true) {

			}
			else {
				outputs.Append("Unknown spell.\n You either do not have this spell or you typed the wrong spell name.\n");
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
			if ((x == 1 && y == 2) || (x == 2 && y == 1)) {
				x = 1; y = 1;
				
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				system("pause");
				enemyStats.Append(enemy1.giveName());
				enemyStats.Append(" | ");
				enemyStats.Append(enemy1.giveHealth());
			}
			else if ((x == 4 && y == 1) || (x == 5 && y == 2)) {
				x = 5; y = 1;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				system("pause");
				enemyStats.Append(enemy2.giveName());
				enemyStats.Append(" | ");
				enemyStats.Append(enemy2.giveHealth());
			}
			else if ((x == 1 && y == 4) || (x == 2 && y == 5)) {
				x = 1; y = 5;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				system("pause");
				enemyStats.Append(enemy3.giveName());
				enemyStats.Append(" | ");
				enemyStats.Append(enemy3.giveHealth());
			}
			else {
				x = 5; y = 5;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				system("pause");
				enemyStats.Append(enemy4.giveName());
				enemyStats.Append(" | ");
				enemyStats.Append(enemy4.giveHealth());
			}
		}
	}

	if (x == 3 && y == 1) {
		if (healDrop1Activate != true) {
			healDrop1Activate = true;
			outputs.Append("You have obtained two healing drops!\n");
			player.addItem("healing drop");
			healdrop.setCount((healdrop.getCount()+2));
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
			healdrop.setCount((healdrop.getCount() + 2));
		}
	}
	if (x == 6 && y == 3) {
		if (shortstaffActivate != true) {
			shortstaffActivate = true;
			outputs.Append("You have obtained a shortstaff!\nThis item equips automatically and increases your spell damage!\n");
			player.addItem("shortstaff");
			if (desolateActivate) {
				desolate.increaseDmg();
			}
			if (exortActivate) {
				exort.increaseDmg();
			}
		}
	}
	if (x == 3 && y == 0) {
		if (!exortActivate) {
			exortActivate = true;
			outputs.Append("You have acquired a new spell!\n\t\tSpell name: Exort\tSpell damage: 15\n");
			player.addSpell("exort");
		}
	}
	if (x == 3 && y == 4) {
		if (!desolateActivate) {
			desolateActivate = true;
			outputs.Append("You have acquired a new spell!\n\t\tSpell name: Desolate\tSpell damage: 10\n");
			player.addSpell("desolate");
		}
	}
	if (x == 3 && y == 6) {
		if (!raActivate) {
			raActivate = true;
			outputs.Append("You have acquired a new spell!\n\t\tSpell name: Ra\tSpell damage: N/A\nThis spell has special functionality\n");
			player.addSpell("ra");
		}
	}

	roomVisited[x][y] = true;
	HUD();
}

void Game::setPlayer(Player player) {
	this->player = player;
}

void Game::setEnemies(Enemy enemy1, Enemy enemy2, Enemy enemy3, Enemy enemy4) {
	this->enemy1 = enemy1;
	this->enemy2 = enemy2;
	this->enemy3 = enemy3;
	this->enemy4 = enemy4;
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

	String::WriteInColor(12, "\n______________________________\n\n");
	if (!(enemyStats.EqualTo(""))) {
		String::WriteInColor(414, enemyStats);
		String::WriteInColor(12, "\n______________________________\n");
	}

	std::cout << std::endl; std::cout << std::endl;
	std::cout << "________--------_______";
	std::cout << std::endl;
	if (mapEnable == true) {
		map.Use(roomVisited, x, y).WriteToConsole();
	}
	std::cout << std::endl;
	std::cout << "________--------_______";
	std::cout << std::endl; std::cout << std::endl; 
	
	String::WriteInColor(8, "type \"command list\" to see all available inputs\n\n\n");
	outputs.Prepend("\t\t\t");
	outputs.WriteInColor(79, outputs);
}
