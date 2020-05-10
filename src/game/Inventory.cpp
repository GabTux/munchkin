#include "Inventory.h"

Inventory::Inventory(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect &buttonPos, SDL_Rect &pilePos) :
PileCard("INVENTORY", "BACK", inCards, buttonPos, pilePos)
{
}

void Inventory::updateValue()
{
	int combatPower = 0;
	for (auto& it: cards)
		if (typeid(it.get()) == typeid(ItemCard))
			combatPower += it->getValue();
	value = combatPower;
}
