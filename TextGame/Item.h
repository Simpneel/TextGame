#pragma once

#include <iostream>
#include "String.h"

class Item {
private:
	String name;
	String description;
	bool isActive;

public:
	Item();
	Item(const Item& item);
	Item(String name, String description);
	Item(String name, String description, bool isActive);
	Item& operator=(const Item& item);
	
	const void Description() const;
	void Use();
};

class HealDrop : public Item {
private:
	int count = 2;
	int HealAmt = 50;
	String description = "This item heals you for half of your maximum HP";
public:
	const void Description() const;
	int getCount();
	void setCount(int newCount);
	float Use(float playerHP);
};

class Map : public Item {
private:
	String description = "This item shows you a map of all rooms you have visited\nRooms only register after you have entered the room";
	bool isRoomVisited;
public:
	const void Description() const;
	String Use(bool roomsVisited[7][7], int x ,int y);
	
};

class Shortstaff : public Item {
private:
	String description = "This item increases the damage of all spells you use by 20%";
	float dmgInc=0.2;
public:
	const void Description() const;
	float Use(float baseDmg) const;
};