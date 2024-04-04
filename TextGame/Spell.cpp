#include "Spell.h"

Spell::Spell() {
	name = "";
	damage = 0;
}

Spell::~Spell() {
}

Spell::Spell(String name, float damage) {
	this->name = name;
	this->damage = damage;
}

void Spell::Cast(Player& playerName) {
	float totalDmg = playerName.giveDamage() + this->damage;
}

bool Spell::Compare(Spell a, Spell b) {
	if (a.name < b.name) {
		return true;
	}
	else {
		return false;
	}
}

void Desolate::Cast(Player& playerName) {
	playerName.setHealth((playerName.giveHealth() - damage));
	return void();
}

void Exort::Cast(Player& playerName) {
	playerName.setHealth((playerName.giveHealth() - damage));
	return void();
}

void Ra::Cast() {
	return void();
}
