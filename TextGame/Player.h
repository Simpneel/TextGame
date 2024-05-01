#pragma once
#include "Item.h"
#include <vector>

class Player {
private:
	std::vector<String> spells;
	std::vector<String> items;
	double dmg;
	String name;
	double health;

public:
	Player();
	Player(String playerName, double dmg, double health);
	~Player();
	String giveName();
	double giveHealth();
	double giveDamage();
	void setHealth(double newHealth);

	void addSpell(String spellName);
	bool FindSpell(String spellName);
	String HUDSpellList();

	void addItem(String itemName);
	bool FindItem(String itemName);
	String HUDItemList();
};

class Enemy : public Player {
private:
	String name;
	double health;
	double dmg;
public:
	Enemy();
	Enemy(String name, double dmg, double health);
	String giveName();
	String giveHealth();
	double giveHealthdouble() const;
	double doDamage();
	void takeDamage(double dmgDone);
};


