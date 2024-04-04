#include "Item.h"
#include <iostream>

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

const void Item::Description() const {
	String::WriteInColor(11, name);
	std::cout << "- ";
	description.WriteToConsole();
	std::cout << "\n";
	/*if (isActive == true) {
		String::WriteInColor(10, "You possess this item\n");
	}
	else {
		String::WriteInColor(12, "You do not possess this item\n");
	}*/
	return void();
}


void Item::Use() {
	if (isActive == true) {
		String::WriteInColor(1, " used!");
	}
	return void();
}

const void HealDrop::Description() const {
	String::WriteInColor(13, "Healing Drop");
	std::cout << "- ";
	this->description.WriteToConsole();
	std::cout << "\n";
	
}

float HealDrop::Use(float playerHP) {
	if (count > 0) {
		return playerHP + HealAmt;
		count--;
	}
	else {
		String::WriteInColor(10, "You do not have any healing drops left");
	}
}

const void Map::Description() const {
	String::WriteInColor(11, "Map"); 
	std::cout << "- ";
	this->description.WriteToConsole();
	return void();
}

String Map::Use(bool roomsVisited[7][7], int x, int y) {
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
	return void();
}

float Shortstaff::Use(float baseDmg) const {
		return baseDmg + (baseDmg * dmgInc);
}
