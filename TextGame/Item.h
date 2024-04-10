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
	
	virtual const void Description() const;
	virtual void Use();
};

class Apple : public Item {
private:
	String name;
	String description;
public:
	Apple();
	const void Description() const override;
	void Use() override;
};

class Torch : public Item {
private:
	String name;
	String description;
public:
	Torch();
	const void Description() const override;
	void Use() override;
};

class Satchel : public Item {
private:
	String name;
	String description;
public:
	Satchel();
	const void Description() const override;
	void Use() override;
};

class HealDrop : public Item {
private:
	int count;
	int HealAmt = 50;
	String description = "This item heals you for half of your maximum HP";
public:
	const void Description() const override;
	int getCount();
	void setCount(int newCount);
	double Use(double playerHP);
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
	double dmgInc=0.33;
public:
	const void Description() const;
	double Use(double baseDmg);
};