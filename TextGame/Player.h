#pragma once
#include "Item.h"
#include <vector>

class Player {
private:
	std::vector<String> spells;
	std::vector<String> items;
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
	void HUDSpellList();

	void addItem(String itemName);
	bool FindItem(String itemName);
	void HUDItemList();
};

class Enemy : public Player {
private:
	String name;
	float health;
	float dmg;
public:
	Enemy();
	Enemy(String name, float dmg, float health);
	String giveName();
	String giveHealth();
	float giveHealthFloat();
	float doDamage();
	void takeDamage(float dmgDone);
};


