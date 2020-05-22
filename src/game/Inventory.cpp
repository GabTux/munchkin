#include "Inventory.h"

Inventory::Inventory(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect &buttonPos, SDL_Rect &pilePos, TTF_Font* inFont) :
PileCard("INVENTORY", "BACK", inCards, buttonPos, pilePos, inFont)
{
}

void Inventory::updateValue()
{
	int combatPower = 0;
	for (auto& it: cards)
		combatPower += it->getValue();
	value = combatPower;
}
