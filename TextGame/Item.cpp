#include "Item.h"
#include <iostream>

Item::Item() {
	name = "itemName";
	description = "itemDesc";
	isActive = false;
}

Item::Item(String name, String description) {
	this->name = name;
	this->description = description;
	isActive = false;
}

Item::Item(String name ,String description, bool isActive) {
	this->name = name;
	this->description = description;
	this->isActive = isActive;
}

Item::Item(const Item& item) {
	name = item.name;
	description = item.description;
	isActive = item.isActive;
}

Item& Item::operator=(const Item& item) {
	name = item.name;
	description = item.description;
	isActive = item.isActive;
	return *this;
}

const void Item::Description() const {
	name.WriteToConsole();
	std::cout << " ";
	description.WriteToConsole();
	std::cout << "\n";
	if (isActive) {
		std::cout << "This item is in your inventory \n";
	}
}


void Item::Use() {
}
