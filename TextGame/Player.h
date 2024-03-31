#pragma once
#include "String.h"
#include "Item.h"
#include <list>

class Player {
private:
	std::list<String> spells;
	float dmg;
	String name;
	float health;

public:
	Player();
	Player(String playerName, float dmg, float health);
	~Player();
	String giveName();
	float giveHealth();
	bool FindSpell(String spellName);
	void dmgBuff(Shortstaff shortstaff) const;
	bool FindItem(String itemName, bool isActive, int itemCount);
};


