#include "Item.h"

class Shortstaff : public Item {
private: 
	bool active = false;

public:
	const void Description() const override;
	void Use() override;

	Shortstaff();
};

const void Shortstaff::Description() const {
	std::cout << "This is a shortstaff, it increases your spell damage on attack spells";
	return void();
}

void Shortstaff::Use() {
	active = true;
}

Shortstaff::Shortstaff() {

}
