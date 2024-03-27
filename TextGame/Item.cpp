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
	if (isActive == true) {
		String::WriteInColor(10, "You possess this item\n");
	}
	else {
		String::WriteInColor(12, "You do not possess this item\n");
	}
	return void();
}


void Item::Use() {
	if (isActive == true) {
		String::WriteInColor(1, " used!");
	}
	return void();
}

const void HealDrop::Description() const {
	String::WriteInColor(11, "Healing Drop");
	std::cout << "- ";
	this->description.WriteToConsole();
	std::cout << "\n";
	
}

int HealDrop::Use() {
	return HealAmt;
}

const void Map::Description() const {
	String::WriteInColor(11, "Map"); 
	std::cout << "- ";
	this->description.WriteToConsole();
	return void();
}

String Map::Use(bool roomsVisited[7][7]) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (roomsVisited[j][i] == true) {
				String::WriteInColor(9, " [] ");
			}
		}
		std::cout << std::endl;
	}
	return "";
}

const void Shortstaff::Description() const {
	return void();
}

float Shortstaff::Use() {
	if (isActive == true) {
		return dmgInc;
	}
}
