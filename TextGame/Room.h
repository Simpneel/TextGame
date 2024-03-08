#pragma once
#include "Item.h"

class Room {
private:
	Item* items;
	String description;
	int itemCount;

public:
	Room();
	Room(String description, Item* items, int itemCount);
	~Room();
	const void Description() const;
};