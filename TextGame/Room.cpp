#include "Room.h"

Room::Room(){
	items = nullptr;
	description = "";
	itemCount = 0;
}

Room::Room(String description, Item* items, int itemCount) {
	this->description = description;
	if (itemCount == 0) {
		this->description.Append("\nThis room has no items in it");
	}
	this->items = new Item[itemCount];
	for (int i = 0; i < itemCount; i++) {
		this->items[i] = items[i];
	}
	this->itemCount = itemCount;
	delete[] items;
}

Room::Room(const Room& room) {
	description = room.description;
	items = new Item[room.itemCount];
	for (int i = 0; i < room.itemCount; i++) {
		items[i] = room.items[i];
	}
	itemCount = room.itemCount;
}

Room& Room::operator=(const Room& room)
{
	delete[] items;
	description = room.description;
	items = new Item[room.itemCount];
	for (int i = 0; i < room.itemCount; i++) {
		items[i] = room.items[i];
	}
	itemCount = room.itemCount;
	return *this;
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
