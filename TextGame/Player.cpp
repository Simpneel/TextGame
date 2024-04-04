#include "Player.h"

Player::Player() {
	name = "";
	dmg = 0;
	health = 0;
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
			break;
		}
		else {
			return false;
		}
	}
}

void Player::HUDSpellList() {

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
			break;
		}
		else {
			return false;
		}
	}
}

void Player::HUDItemList() {

}

Enemy::Enemy() {
	name = "";
	health = 0.0;
	dmg = 0.0;
}

Enemy::Enemy(String name, float dmg, float health) {
	this->name = name;
	this->health = health;
	this->dmg = dmg;
}

String Enemy::giveName() {
	return name;
}

String Enemy::giveHealth() {
	return String(health);
}

float Enemy::giveHealthFloat() {
	return health;
}

float Enemy::doDamage() {
	return dmg;
}

void Enemy::takeDamage(float dmgDone) {
	health = health - dmgDone;
	return void();
}
