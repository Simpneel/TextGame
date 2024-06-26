#include "Item.h"
#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

Item::Item() {
	name = "";
	description = "";
	isActive = false;
}

Item::Item(String name, String description) {
	this->name = name;
	this->description = description;
	isActive = false;
}

Item::Item(String name ,String description, bool isActive) {
	this->name = name;
	this->description = description;
	this->isActive = isActive;
}

Item::Item(const Item& item) {
	name = item.name;
	description = item.description;
	isActive = item.isActive;
}

Item& Item::operator=(const Item& item) {
	name = item.name;
	description = item.description;
	isActive = item.isActive;
	return *this;
}

Item::~Item() {
	delete this;
}

const void Item::Description() const {
	String::WriteInColor(11, name);
	std::cout << "- ";
	description.WriteToConsole();
	std::cout << "\n";
	return void();
}


void Item::Use() {
	if (isActive == true) {
		String::WriteInColor(1, " used!");
	}
	return void();
}

Apple::Apple() {
	name = "Apple";
	description = "This is an apple, you can eat it or just throw it at something to see what happens\n";
}

const void Apple::Description() const {
	String::WriteInColor(11, name);
	std::cout << "- ";
	description.WriteToConsole();
	//std::this_thread::sleep_for(std::chrono::seconds(3));
	String::WriteInColor(2, "\t\t\t\t\t\t\t\t\t\t\t\t          //		   \n");
	String::WriteInColor(6, "\t\t\t\t\t\t\t\t\t\t\t\t          |		   \n");
	String::WriteInColor(12, "\t\t\t\t\t\t\t\t\t\t\t\t        @@@@@        \n");
	String::WriteInColor(12, "\t\t\t\t\t\t\t\t\t\t\t\t    @@@@@@@@@@@@@    \n");
	String::WriteInColor(12, "\t\t\t\t\t\t\t\t\t\t\t\t   @@@@@@@@@@@@@@@   \n");
	String::WriteInColor(12, "\t\t\t\t\t\t\t\t\t\t\t\t   @@@@@@@@@@@@@@@   \n");
	String::WriteInColor(12, "\t\t\t\t\t\t\t\t\t\t\t\t   @@@@@@@@@@@@@@@   \n");
	String::WriteInColor(12, "\t\t\t\t\t\t\t\t\t\t\t\t     @@@@@@@@@@@     \n");
	String::WriteInColor(12, "\t\t\t\t\t\t\t\t\t\t\t\t      @@@@ @@@@      \n");
	String::WriteInColor(12, "\n");
	return void();
}

void Apple::Use() {
	String::WriteInColor(7, "Do you wish to eat the apple or throw it?\n");
	String tempInput;
	tempInput.ReadFromConsole().ToLower();
	if (tempInput == "eat") { String::WriteInColor(7, "It was spoiled, oops\n\n"); }
	else if (tempInput == "throw") { String::WriteInColor(11, "Thank god you threw it, a worm popped out!\n"); }
	else {String::WriteInColor(10, "Incorrect input, you put the apple away\n"); }
	std::this_thread::sleep_for(std::chrono::seconds(4));
	return void();
}

Torch::Torch() {
	name = "Torch";
	description = "The torch illuminates your path and helps you travese through dark rooms\n";
}

const void Torch::Description() const {
	String::WriteInColor(11, name);
	std::cout << "- ";
	description.WriteToConsole();
	String::WriteInColor(70, "\t\t\t\t\t\t\t\t\t\t\t\t	 @ \n");
	String::WriteInColor(70, "\t\t\t\t\t\t\t\t\t\t\t\t	  @  \n");
	String::WriteInColor(70, "\t\t\t\t\t\t\t\t\t\t\t\t	    @ \n");
	String::WriteInColor(70, "\t\t\t\t\t\t\t\t\t\t\t\t	  @  @   \n");
	String::WriteInColor(70, "\t\t\t\t\t\t\t\t\t\t\t\t	 @@@   @\n");
	String::WriteInColor(70, "\t\t\t\t\t\t\t\t\t\t\t\t	 @   @ \n");
	String::WriteInColor(78, "\t\t\t\t\t\t\t\t\t\t\t\t	@@@@\n");
	String::WriteInColor(104, "\t\t\t\t\t\t\t\t\t\t\t\t	///\n");
	String::WriteInColor(104, "\t\t\t\t\t\t\t\t\t\t\t\t	 /\n");
	String::WriteInColor(104, "\t\t\t\t\t\t\t\t\t\t\t\t	 /\n");
	String::WriteInColor(104, "\t\t\t\t\t\t\t\t\t\t\t\t	 /\n");
	std::cout << "\n";
	return void();

}

void Torch::Use() {
	String::WriteInColor(10, "You lit up the torch! Everything is bright and clear now.\n\n");
	std::this_thread::sleep_for(std::chrono::seconds(4));
	return void();
}

Satchel::Satchel() {
	name = "Satchel";
	description = "This satchel holds your items for you, do not lose it.\n";
}

const void Satchel::Description() const {
	String::WriteInColor(11, name);
	std::cout << "- ";
	description.WriteToConsole();
	std::cout << "\n";
	return void();
}

void Satchel::Use() {
	String::WriteInColor(10, "You stashed your items away in satchel.\n");
	std::this_thread::sleep_for(std::chrono::seconds(4));
	return void();
}

const void HealDrop::Description() const  {
	String::WriteInColor(13, "Healing Drop");
	std::cout << "- ";
	this->description.WriteToConsole();
	std::cout << "\n";
}

int HealDrop::getCount() {
	return count;
}

void HealDrop::setCount(int newCount) {
	count = newCount;
	return void();
}

double HealDrop::Use(double playerHP) {
	if (count > 0) {
		return playerHP + HealAmt;
		count--;
	}
	else {
		String::WriteInColor(10, "You do not have any healing drops left\n");
	}
}

const void Map::Description() const {
	String::WriteInColor(13, "Map"); 
	std::cout << "- ";
	this->description.WriteToConsole();
	return void();
}

String Map::Use(bool roomsVisited[7][7]) {
	String map = "[ST]";
	int westCount = 0;
	int eastCount = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (roomsVisited[i][j] == true) {
				if (j == 3 && i == 2) {
					map.Prepend("[W]");
					westCount++;
				}
				else if (j == 3 && i == 1) {
					map.Prepend("[W]");
					westCount++;
				}
				else if (j == 3 && i == 0) {
					map.Prepend("[W]");
					westCount++;
				}
				else if (j == 3 && i > 3) {
					map.Replace("[ST]", "[ST][E]");
				}
				else if (i == 3 && j < 3) {
					if (westCount == 0) {
						map.Prepend("\n");
						map.Prepend("[N]");
					}
					else if (westCount == 1) {
						map.Prepend("\n");
						map.Prepend("   [N]");
					}
					else if (westCount == 2) {
						map.Prepend("\n");
						map.Prepend("      [N]");
					}
					else {
						map.Prepend("\n");
						map.Prepend("         [N]");
					}
				}
				else if (i == 3 && j > 3) {
					if (westCount == 0) {
						map.Append("\n");
						map.Append("[S]");
					}
					else if (westCount == 1) {
						map.Append("\n");
						map.Append("   [S]");
					}
					else if (westCount == 2) {
						map.Append("\n");
						map.Append("      [S]");
					}
					else {
						map.Append("\n");
						map.Append("         [S]");
					}
				}
			}
		}
	}
	return map;
}

const void Shortstaff::Description() const {
	String::WriteInColor(13, "Shortstaff");
	std::cout << "- ";
	this->description.WriteToConsole();
	std::cout << "\n";
	return void();
}

double Shortstaff::Use(double baseDmg) {
		return baseDmg + (baseDmg * dmgInc);
}
