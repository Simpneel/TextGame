#include "Player.h"

Player::Player() {
	name = "playerName";
	dmg = 0;
}

Player::Player(String playerName, float dmg, float health) {
	this->health = health;
	name = playerName;
	this->dmg = dmg;
}

Player::~Player() {
}

String Player::giveName() {
	return name;
}

float Player::giveHealth() {
	return health;
}

float Player::giveDamage() {
	return dmg;
}

bool Player::FindSpell(String spellname) {
	return false;
}

void Player::dmgBuff(Shortstaff shortstaff) const {
	shortstaff.Use(dmg);
}

bool Player::FindItem(String itemName) {
	return false;
}
