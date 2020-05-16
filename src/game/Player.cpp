#include "Player.h"

Player::Player(std::vector<std::shared_ptr<Card>> &inHandCards, SDL_Rect &inPosition)
: position(inPosition)
{
	SDL_Rect buttonPos = inPosition;
	buttonPos.x += 5;
	buttonPos.y += 5;
	SDL_Rect pilePos = buttonPos;
	pilePos.x += 500;
	handCards = std::make_unique<HandCards>(inHandCards, buttonPos, pilePos);
	handCards->updateValue();
	buttonPos.y += 70;
	pilePos.x -= 150;
	std::vector<std::shared_ptr<Card>> emptyInv;
	inventory = std::make_unique<Inventory>(emptyInv, buttonPos, pilePos);
	inventory->updateValue();
}

void Player::setHandCards(std::vector<std::shared_ptr<Card>>& inHandCards)
{
	handCards->setCards(inHandCards);
	handCards->updateValue();
}

void Player::setInvCards(std::vector<std::shared_ptr<Card>> &inHandCards)
{
	inventory->setCards(inHandCards);
}

void Player::setDefault()
{
	handCards->setDefault();
	inventory->setDefault();
}

void Player::gotCard(std::shared_ptr<Card> inCard)
{
	handCards->addCard(inCard);
	handCards->updateValue();
}
