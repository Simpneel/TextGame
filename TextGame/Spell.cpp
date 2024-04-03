#include "Spell.h"

Spell::Spell() {
	name = "";
	description = "";
	damage = 0;
}

Spell::~Spell() {
}

Spell::Spell(String name, String description, float damage) {
	this->name = name;
	this->description = description;
	this->damage = damage;
}

void Spell::Cast(Player& playerName) {
	float totalDmg = playerName.giveDamage() + this->damage;
}

void Spell::Cast(Player& playerName, Item itemName) {

}

bool Spell::Compare(Spell a, Spell b) {

	return false;
}

void Desolate::Cast(Player playerName) {

}
