#include "Human.h"

Human::Human(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition, SDLResources& inRes,
						 std::shared_ptr<CardDeck>& doorDeckGarbage, std::shared_ptr<CardDeck>& treasureDeckGarbage) :
Player(inHandCards, inPosition, inRes, doorDeckGarbage, treasureDeckGarbage)
{

}

void Human::handleEvent(SDL_Event &event)
{
	if (handCards->getState() == PileState::UNPACKED)
		handCards->handleEvent(event);
	else if (inventory->getState() == PileState::UNPACKED)
		inventory->handleEvent(event);
	else
	{
		inventory->handleEvent(event);
		handCards->handleEvent(event);
	}
}

Human::~Human()
{
	handCards.reset();
	inventory.reset();
}

void Human::update(std::shared_ptr<Card>& inActCard, GameState inActState)
{
	handCards->update(inActCard, inActState);
	inventory->update(inActCard, inActState);
	levelIndicator->update();
	powerIndicator->update();
}
