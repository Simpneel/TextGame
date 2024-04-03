#pragma once
#include "String.h"
#include "Player.h"

class Spell {
private:
	String name;
	String description;
	float damage = 0;

public:
	Spell();
	~Spell();
	Spell(String name, String description, float damage);
	void Cast(Player& playerName);
	void Cast(Player& playerName, Item itemName);
	static bool Compare(Spell a, Spell b);
};

class Desolate : public Spell {
private:
	String name;
	String description;
	float damage = 10;
public:
	void Cast(Player playerName);
};