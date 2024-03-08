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