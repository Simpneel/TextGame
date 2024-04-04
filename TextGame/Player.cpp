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

void Player::setHealth(float newHealth) {
	health = newHealth;
	return void();
}

void Player::addSpell(String spellName) {
	spells.push_back(spellName);
	return void();
}

bool Player::FindSpell(String spellname) {
	spells.sort();
	std::list<String>::iterator it;
	for (it = spells.begin(); it != spells.end(); it++) {
		if (spellname.EqualTo(*it)) {
			return true;
		}
		else {
			return false;
		}
	}
}

void Player::dmgBuff(Shortstaff shortstaff) const {
	shortstaff.Use(dmg);
}

void Player::addItem(String itemName) {
	items.push_back(itemName);
	return void();
}

bool Player::FindItem(String itemName) {
	items.sort();
	std::list<String>::iterator it;
	for (it = items.begin(); it != items.end(); it++) {
		if (itemName.EqualTo(*it)) {
			return true;
		}
		else {
			return false;
		}
	}
}
