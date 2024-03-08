#pragma once
#include "String.h"
#include "Player.h"

class Spell {
private:
	String name;
	int damage;

public:
	Spell(String name, int damage);
	void Cast(Player& playerName);
	void Cast(Player& playerName, Item itemName);
	static bool Compare(Spell a, Spell b);
};