#pragma once
#include "String.h"
#include "Player.h"

class Spell {
private:
	String name;
	float damage = 0;

public:
	Spell();
	~Spell();
	Spell(String name, float damage);
	void Cast();
	static bool Compare(Spell a, Spell b);
};

class Desolate : public Spell {
private:
	String name = "Desolate";
	float damage = 10;
public:
	void Cast(Enemy& enemy);
};

class Exort : public Spell {
private:
	String name = "Exort";
	float damage = 15;
public:
	void Cast(Enemy& enemy);
};

class Ra : public Spell {
private:
	String name = "Ra";
	float damage = 0;
public:
	void Cast();
};