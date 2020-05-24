#include "Player.h"

Player::Player(std::vector<std::shared_ptr<Card>> &inHandCards, SDL_Rect &inPosition, SDLResources& inRes,
							 std::shared_ptr<CardDeck>& inDoorDeckGarbage, std::shared_ptr<CardDeck>& inTreasureDeckGarbage)
: position(inPosition), res(inRes), doorDeckGarbage(inDoorDeckGarbage), treasureDeckGarbage(inTreasureDeckGarbage)
{
	SDL_Rect buttonPos = inPosition;
	buttonPos.x += 5;
	buttonPos.y += 5;
	SDL_Rect pilePos = buttonPos;
	pilePos.x += 500;
	handCards = std::make_unique<HandCards>(inHandCards, buttonPos, pilePos, res.menuFont, doorDeckGarbage, treasureDeckGarbage);
	handCards->updateValue();
	buttonPos.y += 70;
	pilePos.x -= 150;
	std::vector<std::shared_ptr<Card>> emptyInv;
	inventory = std::make_unique<Inventory>(emptyInv, buttonPos, pilePos, res.menuFont, doorDeckGarbage, treasureDeckGarbage);
	inventory->updateValue();

	levelIndicator = std::make_unique<Text>(std::string("LEVEL "+std::to_string(level)),
					SDL_Rect({position.x, constants::levelIndY+position.y, 0, 0}), res.menuFont, SDL_Color({255, 255, 255}), res.mainRenderer);
	powerIndicator = std::make_unique<Text>(std::string("POWER "+std::to_string(level)),
	                                        SDL_Rect({position.x, constants::powerIndY+position.y, 0, 0}), res.menuFont, SDL_Color({255, 255, 255}), res.mainRenderer);
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
	level = 1;
	levelIndicator->setDefault();
	levelIndicator->setText("LEVEL "+std::to_string(level));
	powerIndicator->setText("POWER "+std::to_string(level+inventory->getValue()+oneTimeBoost));
}

void Player::gotCard(const std::shared_ptr<Card>& inCard)
{
	handCards->addCard(inCard);
	handCards->updateValue();
}

bool Player::endTurn(std::string& inString)
{
	if (handCards->getValue() > constants::maxHandCards)
	{
		inString += "You have " + std::to_string(handCards->getValue()) +
		            " cards but max is " + std::to_string(constants::maxHandCards) + " cards.\nThrow some away! (Card->play->throw).";
		return false;
	}
	endTurn();
	return true;
}

void Player::loseCards(int loseCardsNum)
{
	if (loseCardsNum >= handCards->getValue())
		loseCardsNum = handCards->getValue();
	for (int i = 0; i < loseCardsNum; i++)
	{
		auto lostCard = handCards->getRandomCard();
		if (lostCard->isTreasure())
			treasureDeckGarbage->addCard(lostCard);
		else
			doorDeckGarbage->addCard(lostCard);
	}
}

void Player::boostPower(int num)
{
	oneTimeBoost += num;
	powerIndicator->setText(std::string("POWER ")+std::to_string(level+inventory->getValue()+oneTimeBoost));
}

void Player::changeLevel(int num)
{
	if (level + num < 1)
		level = 1;
	else
		level += num;
	levelIndicator->setText(std::string("LEVEL ")+std::to_string(level));
	powerIndicator->setText(std::string("POWER ")+std::to_string(level+inventory->getValue()+oneTimeBoost));
}

void Player::toInvCard(std::shared_ptr<Card>& inCard)
{
	inCard->setDefault();
	inventory->addCard(inCard);
	inventory->updateValue();
	powerIndicator->setText(std::string("POWER ")+std::to_string(level+inventory->getValue()+oneTimeBoost));
}

int Player::getCombatPower()
{
	return oneTimeBoost + inventory->getValue() + level;
}

void Player::render(SDL_Renderer* renderer)
{
	handCards->render(renderer);
	inventory->render(renderer);
	levelIndicator->render(renderer);
	powerIndicator->render(renderer);
}

void Player::resetBoost()
{
	oneTimeBoost = 0;
	powerIndicator->setText(std::string("POWER ")+std::to_string(level+inventory->getValue()+oneTimeBoost));
}

void Player::setOpp(std::shared_ptr<Player> &inOpp)
{
	handCards->setPlayers(shared_from_this(), inOpp);
	inventory->setPlayers(shared_from_this(), inOpp);
}

void Player::updateIndicators()
{
	powerIndicator->setText(std::string("POWER ")+std::to_string(level+inventory->getValue()+oneTimeBoost));
	levelIndicator->setText(std::string("LEVEL ")+std::to_string(level));
}

void Player::startTurn()
{
	handCards->unpack();
}

void Player::endTurn()
{
	handCards->pack();
	inventory->pack();
}
