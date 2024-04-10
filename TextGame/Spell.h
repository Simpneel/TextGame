#pragma once
#include "String.h"
#include "Player.h"

class Spell {
private:
	String name;
	double damage = 0;

public:
	Spell();
	~Spell();
	Spell(String name, double damage);
	void Cast();
	static bool Compare(Spell a, Spell b);
};

class Desolate : public Spell {
private:
	String name = "Desolate";
	double damage = 10;
public:
	void Cast(Enemy& enemy);
	void increaseDmg();
};

class Exort : public Spell {
private:
	String name = "Exort";
	double damage = 20;
public:
	void Cast(Enemy& enemy);
	void increaseDmg();
};

class Ra : public Spell {
private:
	String name = "Ra";
	double damage = 0;
public:
	void Cast(Player& player, Enemy& enemy);
};