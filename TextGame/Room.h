#pragma once
#include "Item.h"
#include "Spell.h"

class Room {
private:
	Item* items;
	String description;
	int itemCount;
	Spell spell;

public:
	Room();
	Room(String description);
	Room(String description, Item* items, int itemCount);
	Room(String description, Spell& spell);
	Room(const Room& room);
	Room& operator=(const Room& room);
	~Room();
	const void Description() const;
};