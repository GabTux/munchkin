#include "Inventory.h"

Inventory::Inventory(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect &buttonPos, SDL_Rect &pilePos, TTF_Font* inFont,
										 std::shared_ptr<CardDeck>& doorDeckGarbage, std::shared_ptr<CardDeck>& treasureDeckGarbage) :
PileCard("INVENTORY", "BACK", inCards, buttonPos, pilePos, inFont, doorDeckGarbage, treasureDeckGarbage)
{
}

void Inventory::updateValue()
{
	int combatPower = 0;
	for (auto& it: cards)
		combatPower += it->getValue();
	value = combatPower;
}
