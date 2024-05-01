#include "Player.h"
#include <algorithm>

Player::Player() {
	name = "";
	dmg = 0;
	health = 0;
}

Player::Player(String playerName, double dmg, double health) {
	this->health = health;
	name = playerName;
	this->dmg = dmg;
}

Player::~Player() {

}

String Player::giveName() {
	return name;
}

double Player::giveHealth() {
	return health;
}

double Player::giveDamage() {
	return dmg;
}

void Player::setHealth(double newHealth) {
	health = newHealth;
	return void();
}

void Player::addSpell(String spellName) {
	spells.push_back(spellName);
	return void();
}

bool Player::FindSpell(String spellname) {
	size_t start, end, mean;
	start = 0;
	end = spells.size();
	mean = (start + end) / 2;
	std::vector<String>::iterator it = spells.begin();
	while (it != spells.end()) {
		if (*it < spellname) {
			start = mean + 1;
		}
		else if (*it == spellname) {
			return true;
		}
		else {
			end = mean - 1;
		}
		it++;
	}
	return false;
}

String Player::HUDSpellList() {
	String spellList;
	std::vector<String>::iterator it = spells.begin();
	while (it != spells.end()) {
		spellList.Append(*it);
		spellList.Append(" ");
		it++;
	}
	return spellList;
}

void Player::addItem(String itemName) {
	items.push_back(itemName);
	return void();
}

bool Player::FindItem(String itemName) {
	size_t start, end, mean;
	start = 0;
	end = spells.size();
	mean = (start + end) / 2;
	std::vector<String>::iterator it = items.begin();
	while (it != items.end()) {
		if (*it < itemName) {
			start = mean + 1;
		}
		else if (*it == itemName) {
			return true;
		}
		else {
			end = mean - 1;
		}
		it++;
	}
	return false;
}

String Player::HUDItemList() {
	String itemList;
	std::vector<String>::iterator it = items.begin();
	while (it != items.end()) {
		itemList.Append(*it);
		itemList.Append(" ");
		it++;
	}
	return itemList;
}

Enemy::Enemy() {
	name = "";
	health = 0.0;
	dmg = 0.0;
}

Enemy::Enemy(String name, double dmg, double health) {
	this->name = name;
	this->health = health;
	this->dmg = dmg;
}

String Enemy::giveName() {
	return name;
}

String Enemy::giveHealth() {
	int healthOutput = int(health * 100 + .5) / 100;
	return String(healthOutput);
}

double Enemy::giveHealthdouble() const {
	return health;
}

double Enemy::doDamage() {
	return dmg;
}

void Enemy::takeDamage(double dmgDone) {
	health = health - dmgDone;
	return void();
}
