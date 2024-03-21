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
		String::WriteInColor(10, "You possess this item\n");
	}
	else {
		String::WriteInColor(12, "You do not possess this item\n");
	}
}


void Item::Use() {
}
