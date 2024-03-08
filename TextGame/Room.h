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
	Room(const Room& room);
	Room& operator=(const Room& room);
	~Room();
	const void Description() const;
};