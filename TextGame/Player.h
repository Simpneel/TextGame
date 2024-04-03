#pragma once
#include "String.h"
#include "Item.h"
#include <list>

class Player {
private:
	std::list<String> spells;
	std::list<Item> items;
	float dmg;
	String name;
	float health;

public:
	Player();
	Player(String playerName, float dmg, float health);
	~Player();
	String giveName();
	float giveHealth();
	float giveDamage();
	bool FindSpell(String spellName);
	void dmgBuff(Shortstaff shortstaff) const;
	bool FindItem(String itemName);
};


