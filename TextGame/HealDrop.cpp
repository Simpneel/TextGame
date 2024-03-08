#include "Item.h"

class HealDrop : public Item {
	const void Description() const override;
	void Use() override;
};

const void HealDrop::Description() const {
	std::cout << "This is a healing droplet";
	return void();
}

void HealDrop::Use() {

}