#include "HandCards.h"

HandCards::HandCards(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect &buttonPos, SDL_Rect &pilePos, TTF_Font* inFont,
										 std::shared_ptr<CardDeck>& doorDeckGarbage, std::shared_ptr<CardDeck>& treasureDeckGarbage) :
PileCard("HAND", "BACK", inCards, buttonPos, pilePos, inFont, doorDeckGarbage, treasureDeckGarbage)
{
}

void HandCards::updateValue()
{
	value = cards.size();
	if (pileState == PileState::PACKED) switchButton->setText("HAND "+std::to_string(value));
}
