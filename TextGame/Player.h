#pragma once
#include "String.h"
#include "Item.h"
#include <list>

class Player {
private:
	std::list<String> spells;
	int dmgMod;

public:
	Player();
	~Player();
	bool FindSpell(String spellName);
	bool FindItem(String itemName)
};