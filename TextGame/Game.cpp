#include "Game.h"
#include <Windows.h>
#include <thread>
#include <chrono>

Game::Game() {
	x = 3, y = 3;

	//Starting room
	rooms[3][3] = Room("Starting room", &apple, 1);
	
	//North rooms
	rooms[3][0] = Room("North room 3", exort);
	rooms[3][1] = Room("North room 2", &healdrop, 1);
	rooms[3][2] = Room("North room 1", &satchel, 1);

	//South rooms
	rooms[3][4] = Room("South room 1", desolate);
	rooms[3][5] = Room("South room 2", nullptr, 0);
	rooms[3][6] = Room("South room 3", ra);
	//move north

	//West rooms
	rooms[2][3] = Room("West room 1", &torch, 1);
	rooms[1][3] = Room("West room 2", &map, 1);
	rooms[0][3] = Room("West room 3", nullptr, 0);

	//East rooms
	rooms[4][3] = Room("East room 1", &healdrop, 1);
	rooms[5][3] = Room("East room 2", nullptr, 0);
	rooms[6][3] = Room("East room 3", &shortstaff, 1);

	//Fight rooms
	rooms[1][1] = Room("Salt Room");
	rooms[5][1] = Room("Cobalt Room");
	rooms[5][5] = Room("Radium Room");
	rooms[1][5] = Room("Xenon Room");
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
	std::cout << "\n";

	userInput.ReadFromConsole();

	String tempStorage = userInput;
	float playerHP = player.giveHealth();

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
		y++;
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
	else if (userInput == "use item") {
		String::WriteInColor(14, "Enter item you wish to use\n");
		String tempInput;
		tempInput.ReadFromConsole().ToLower();
		if (tempInput == "apple") { apple.Use(); }
		else if (tempInput == "satchel") { satchel.Use(); }
		else if (tempInput == "torch") { torch.Use(); }
		else if (tempInput == "shortstaff") {
			if (shortstaffActivate) { outputs.Append("Item is already in use\n"); }
			else { outputs.Append("Unknown item, you time traveller\n"); }
		}
		else if (tempInput == "map" && mapActivate == true) { mapEnable = true; }
		else if (tempInput == "healing orb") { outputs.Append("Use the command \"heal\" to use healing orbs\n"); }
		else { outputs.Append("Unknown item name, please try again\n"); }
	}
	else if (userInput == "attack") {
		if ((x == 1 || x == 5) && (y == 1 || y == 5)) {
			if (x == 1 && y == 1) {
				outputs.Append(enemy1.giveName());
				enemy1.takeDamage(player.giveDamage());
				outputs.Append(" was hit!\n");
			}
			else if (x == 5 && y == 1) {
				outputs.Append(enemy2.giveName());
				enemy2.takeDamage(player.giveDamage());
				outputs.Append(" was hit!\n");
			}
			else if (x == 5 && y == 5) {
				outputs.Append(enemy3.giveName());
				enemy3.takeDamage(player.giveDamage());
				outputs.Append(" was hit!\n");
			}
			else if (x == 1 && y == 5) {
				outputs.Append(enemy4.giveName());
				enemy4.takeDamage(player.giveDamage());
				outputs.Append(" was hit!\n");
			}
		}
		else {
			outputs.Append("There is no enemy here to attack, what are you doing?\n");
		}
	}
	else if (userInput == "cast spell") {
		String::WriteInColor(14, "\nEnter spell name to cast\n");
		String tempInput;
		tempInput.ReadFromConsole();
		tempInput.ToLower();
		if (/*player.FindSpell(tempInput) == */true) {
			if (tempInput == "desolate" && desolateActivate == true) {
				if (x == 1 && y == 1) {
					outputs.Append(enemy1.giveName());
					outputs.Append(" was hit!\n");
					desolate.Cast(enemy1);
				}
				else if (x == 5 && y == 1) {
					outputs.Append(enemy2.giveName());
					outputs.Append(" was hit!\n");
					desolate.Cast(enemy2);
				}
				else if (x == 5 && y == 5) {
					outputs.Append(enemy3.giveName());
					outputs.Append(" was hit!\n");
					desolate.Cast(enemy3);
				}
				else if (x == 1 && y == 5) {
					outputs.Append(enemy4.giveName());
					outputs.Append(" was hit!\n");
					desolate.Cast(enemy4);
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
				}
				else if (x == 5 && y == 1) {
					outputs.Append(enemy2.giveName());
					outputs.Append(" was hit!\n");
					exort.Cast(enemy2);
				}
				else if (x == 5 && y == 5) {
					outputs.Append(enemy3.giveName());
					outputs.Append(" was hit!\n");
					exort.Cast(enemy3);
				}
				else if (x == 1 && y == 5) {
					outputs.Append(enemy4.giveName());
					outputs.Append(" was hit!\n");
					exort.Cast(enemy4);
				}
				else {
					outputs.Append("Who are you casting this on?\n\t\t\tNo enemies nearby\n");
				}
			}
			else if (tempInput == "ra" && raActivate == true) {
				if (x == 1 && y == 1) {
					outputs.Append(enemy1.giveName());
					outputs.Append(" was hit!\n");
					ra.Cast(player, enemy1);
				}
				else if (x == 5 && y == 1) {
					outputs.Append(enemy2.giveName());
					outputs.Append(" was hit!\n");
					ra.Cast(player, enemy2);
				}
				else if (x == 5 && y == 5) {
					outputs.Append(enemy3.giveName());
					outputs.Append(" was hit!\n");
					ra.Cast(player, enemy3);
				}
				else if (x == 1 && y == 5) {
					outputs.Append(enemy4.giveName());
					outputs.Append(" was hit!\n");
					ra.Cast(player, enemy4);
				}
				else {
					outputs.Append("Who are you casting this on?\n\t\t\tNo enemies nearby\n");
				}
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
		outputs.Append("USE ITEM- Prompts you to type an item name in and use it\n");
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
			if (((x == 1 && y == 2) || (x == 2 && y == 1)) && enemy1Alive == true) {
				x = 1; y = 1;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				enemyStats.Append("Lanesra: I'm going to use these brass knuckles to make you feel the pain I feel every day!\nI want your face to look as red as my Valorant career tab's red carpet...\n");
			}
			else if (((x == 4 && y == 1) || (x == 5 && y == 2)) && enemy2Alive == true) {
				x = 5; y = 1;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				enemyStats.Append("Kurt: My guitar has a shotgun built into it!\nI'll make sure it blows your head off before it blows mine off!\n");
			}
			else if (((x == 4 && y == 5) || (x == 5 && y == 4)) && enemy3Alive == true) {
				x = 5; y = 5;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				enemyStats.Append("Ilton: I use HAM(ilton) to beat those winged bulls and now I'll use it to beat you!\nI was given a knighthood cause of my speed so you won't see my attacks coming!\n");
			}
			else if (((x == 1 && y == 4) || (x == 2 && y == 5)) && enemy4Alive == true) {
				x = 1; y = 5;
				outputs.Append("\nYOU ENTERED AN ENEMY ROOM!\n");
				outputs.Append("KILL THE ENEMY TO ESCAPE\n");
				enemyStats.Append("Orion: My belt is said to be as enchanting as the stars in the sky.\nIs it in your constellations to handle it's power?\n");

			}
			else {
				outputs.Append("An unbreakable wall stops you from going that way. Try going a different way\n");
				x = tempLocStorage[0];
				y = tempLocStorage[1];
			}
		}
	}

	if (x == 1 && y == 1) {
		outputs.Append("Salt Room\n");
		if (enemy1.giveHealthFloat() >= 0.1) {
			enemyStats.Append(enemy1.giveName());
			enemyStats.Append(" | ");
			enemyStats.Append(enemy1.giveHealth());
			enemyStats.Append("\n attacked you!");
			player.setHealth(player.giveHealth() - enemy1.doDamage());
		}
		else {
			enemyStats.Append("Lanesra: Beaten once again by some scrubs, why does this always happen to me?");
			enemyStats.Append("\nLanesra has been defeated\n");
			outputs.Append("\nYOU HAVE BEAT THE BOSS ROOM!\nYOU WILL BE TELEPORTED BACK TO THE STARTING ROOM\nYOU WILL BE HEALED FOR 30 HP\nGOOD WORK\n\n");
			player.setHealth(playerHP + 30);
			enemy1Alive = false;
			x = 3, y = 3;
		}
	}
	else if (x == 5 && y == 1) {
		outputs.Append("Cobalt Room\n");
		if (enemy2.giveHealthFloat() >= 0.1) {
			enemyStats.Append(enemy2.giveName());
			enemyStats.Append(" | ");
			enemyStats.Append(enemy2.giveHealth());
			enemyStats.Append("\n attacked you!");
			player.setHealth(player.giveHealth() - enemy2.doDamage());
		}
		else {
			enemyStats.Append("Kurt: This fight went harder than any of my songs ever did");
			enemyStats.Append("\nKurt has been defeated\n");
			outputs.Append("\nYOU HAVE BEAT THE BOSS ROOM!\nYOU WILL BE TELEPORTED BACK TO THE STARTING ROOM\nGOOD WORK\n\n");
			enemy2Alive = false;
			x = 3, y = 3;
		}
	}
	else if (x == 5 && y == 5) {
		outputs.Append("Radium Room\n");
		if (enemy3.giveHealthFloat() >= 0.1) {
			enemyStats.Append(enemy3.giveName());
			enemyStats.Append(" | ");
			enemyStats.Append(enemy3.giveHealth());
			enemyStats.Append("\n attacked you!");
			player.setHealth(player.giveHealth() - enemy3.doDamage());
		}
		else {
			enemyStats.Append("Ilton: NO NO NO THIS CAN'T BE HAPPENING!\nI WAS MEANT TO BE WORLD CHAMPION AGAIN!");
			enemyStats.Append("\nIlton has been defeated\n");
			outputs.Append("\nYOU HAVE BEAT THE BOSS ROOM!\nYOU WILL BE TELEPORTED BACK TO THE STARTING ROOM\nGOOD WORK\n\n");
			enemy3Alive = false;
			x = 3, y = 3;
		}
	}
	else if (x == 1 && y == 5) {
		outputs.Append("Xenon Room\n");
		if (enemy4.giveHealthFloat() >= 0.1) {
			enemyStats.Append(enemy4.giveName());
			enemyStats.Append(" | ");
			enemyStats.Append(enemy4.giveHealth());
			enemyStats.Append("\n attacked you!");
			player.setHealth(player.giveHealth() - enemy4.doDamage());
		}
		else {
			enemyStats.Append("Orion: I'll be back in a year. If you wish to find me, just look up.");
			enemyStats.Append("\nOrion has been defeated\n");
			outputs.Append("\nYOU HAVE BEAT THE BOSS ROOM!\nYOU WILL BE TELEPORTED BACK TO THE STARTING ROOM\nGOOD WORK\n\n");
			enemy4Alive = false;
			x = 3, y = 3;
		}
	}

	if (x == 3 && y == 1) {
		if (healDrop1Activate != true) {
			healDrop1Activate = true;
			outputs.Append("You have obtained two healing drops!\n");
			player.addItem("healing drop");
			healdrop.setCount((healdrop.getCount() + 2));
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
			healdrop.setCount((healdrop.getCount() + 2));
		}
	}
	if (x == 6 && y == 3) {
		if (shortstaffActivate != true) {
			shortstaffActivate = true;
			outputs.Append("You have obtained a shortstaff!\nThis item equips automatically and increases your spell damage!\n");
			player.addItem("shortstaff");
			desolate.increaseDmg();
			exort.increaseDmg();
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
			outputs.Append("You have acquired a new spell!\n\t\tSpell name: Ra\tSpell damage: 5\nThis spell has special functionality\nIt heals you for 25 hp and does 5 damage to the enemy at the same time!\n");
			player.addSpell("ra");
		}
	}

	if (playerHP < 0) {
		String::WriteInColor(79, "YOU DIED\n");
		String::WriteInColor(7, "Better luck next time!\n");
		String::WriteInColor(7, "Game will close automatically in 10 seconds\n\nGives you some time to contemplate how you managed to lose a text based game.");
		std::this_thread::sleep_for(std::chrono::seconds(10));
		keepGameRunning = false;
	}
	if (enemy1Alive == false && enemy2Alive == false && enemy3Alive == false && enemy4Alive == false) {
		gameWon = true;
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
	std::cout << x << " " << y << std::endl;
	String printItems = player.HUDItemList();
	String printSpells = player.HUDSpellList();
	std::cout << "items in inventory: ";
	String::WriteInColor(11, printItems);
	std::cout << std::endl;
	std::cout << "spells learned: ";
	String::WriteInColor(11, printSpells);

	String::WriteInColor(12, "\n______________________________\n");
	if (!(enemyStats.EqualTo(""))) {
		String::WriteInColor(79, enemyStats);
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
	String::WriteInColor(1111, "\t\t\toutput box:\n");
	outputs.Prepend("\t\t\t");
	outputs.WriteInColor(1111, outputs);
	std::cout << std::endl;
}