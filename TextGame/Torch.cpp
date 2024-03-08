#include "Item.h"

class Torch : public Item {
	const void Description() const override;
	void Use() override;
};

const void Torch::Description() const {
	std::cout << "This is a torch, it lights up dark rooms";
	return void();
}

void Use() {

}