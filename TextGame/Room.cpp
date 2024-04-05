#include "Room.h"

Room::Room() {
	item = nullptr;
	description = "";
	itemCount = 0;
}

Room::Room(String description) {
	this->description = description;
	itemCount = 0;
	item = nullptr;
}

Room::Room(String description, Item* item, int itemCount) {
	this->description = description;
	if (itemCount == 0) {
		this->description.Append("\nThis room has no items in it");
	}
	this->item = item;
	this->itemCount = itemCount;
}

Room::Room(String description, Spell& spell) {
	this->description = description;
	this->spell = spell;
	itemCount = 0;
}

Room::Room(const Room& room) {
	description = room.description;
	item = room.item;
	itemCount = room.itemCount;
}

Room& Room::operator=(const Room& room)
{
	description = room.description;
	item = room.item;
	itemCount = room.itemCount;
	return *this;
}

Room::~Room() {

}

const void Room::Description() const {
	description.WriteToConsole();
	std::cout << "\n";
	for (int i = 0; i < itemCount; i++) {
		item[i].Description();
	}
}
