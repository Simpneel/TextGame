#include "Room.h"
#include <iostream>

Room::Room(){
	items = nullptr;
	description = "roomDesc";
	itemCount = 0;
}

Room::Room(String description, Item* items, int itemCount) {
	this->description = description;
	this->items = items;
	this->items = new Item[itemCount];
	for (int i = 0; i < itemCount; i++) {
		this->items[i] = items[i];
	}
	this->itemCount = itemCount;
}

Room::~Room() {
	delete[] items;
}


const void Room::Description() const {
	description.WriteToConsole();
	std::cout << "\n";
	for (int i = 0; i < itemCount; i++) {
		items[i].Description();
	}
	//items.Description();
}
