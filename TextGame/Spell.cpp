#include "Spell.h"

Spell::Spell() {
	name = "";
	damage = 0;
}

Spell::~Spell() {
}

Spell::Spell(String name, double damage) {
	this->name = name;
	this->damage = damage;
}

void Spell::Cast() {
	return void();
}

bool Spell::Compare(Spell a, Spell b) {
	if (a.name < b.name) {
		return true;
	}
	else {
		return false;
	}
}

void Desolate::Cast(Enemy& enemy) {
	enemy.takeDamage(damage);
	return void();
}

void Desolate::increaseDmg() {
	Shortstaff shortstaff;
	damage = shortstaff.Use(damage);
}

void Exort::Cast(Enemy& enemy) {
	enemy.takeDamage(damage);
	return void();
}

void Exort::increaseDmg() {
	Shortstaff shortstaff;
	damage = shortstaff.Use(damage);
}

void Ra::Cast(Player& player, Enemy& enemy) {
	player.setHealth(player.giveHealth() + 25);
	enemy.takeDamage(5);
	return void();
}
