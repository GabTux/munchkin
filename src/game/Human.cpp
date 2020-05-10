#include "Human.h"

Human::Human(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition) :
Player(inHandCards, inPosition)
{

}

void Human::render(SDL_Renderer *renderer)
{
	handCards->render(renderer);
	inventory->render(renderer);
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

void Human::update()
{
	handCards->update();
	inventory->update();
}

Human::~Human()
{
	handCards.reset();
	inventory.reset();
}
