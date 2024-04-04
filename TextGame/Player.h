#pragma once
#include "String.h"
#include "Item.h"
#include <list>

class Player {
private:
	std::list<String> spells;
	std::list<String> items;
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
	void setHealth(float newHealth);
	void addSpell(String spellName);
	bool FindSpell(String spellName);
	void dmgBuff(Shortstaff shortstaff) const;
	void addItem(String itemName);
	bool FindItem(String itemName);
};


