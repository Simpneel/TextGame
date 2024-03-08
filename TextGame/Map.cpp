#include "Item.h"

class Map : public Item {
	const void Description() const override;
	void Use() override;
};

const void Map::Description() const {
	std::cout << "This is a map, it shows you the map grid of every room you've explored";
	return void();
}

void Map::Use() {
	return void();
}