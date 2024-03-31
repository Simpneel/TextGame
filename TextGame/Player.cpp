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

Player::~Player()
{
}

String Player::giveName() {
	return name;
}

float Player::giveHealth() {
	return health;
}

bool Player::FindSpell(String spellname) {
	return false;
}

void Player::dmgBuff(Shortstaff shortstaff) const {
	shortstaff.Use(dmg);
}

bool Player::FindItem(String itemName, bool isActive, int itemCount) {
	if (isActive == true && itemCount > 0) {
		String::WriteInColor(7, "You have this item!\n");
		std::cout << itemCount + " available in inventory.\n";
		return true;
	}
	else if (isActive == true && itemCount == 0) {
		String::WriteInColor(7, "You don't have this item.\n");
		std::cout << "Current count - 0\n";
		return false;
	}
	else {
		String::WriteInColor(7, "Item not found\n");
		return false;
	}
}
