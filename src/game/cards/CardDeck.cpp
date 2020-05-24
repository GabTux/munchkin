#include "CardDeck.h"

CardDeck::CardDeck(std::shared_ptr<CardDeck> &inRecovery) : recoveryDeck(inRecovery)
{
}

std::shared_ptr<Card> CardDeck::getCard()
{
	if (cards.empty())
	{
		if (!recoveryDeck)
		{
			std::string message = "No cards in deck.";
			throw GameError(message);
		}
		else
		{
			while (recoveryDeck->countCards())
				addCard(recoveryDeck->getCard());
		}
	}
	int rChoice = randomInt(0, cards.size()-1);
	std::shared_ptr<Card> res = cards[rChoice];
	cards.erase(cards.begin()+rChoice);
	return res;
}

void CardDeck::setDefault()
{
	for (auto& it: cards)
	{
		it->throwAway();
		it->setDefault();
	}
}

void CardDeck::addCard(std::shared_ptr<Card> inCard)
{
	cards.push_back(std::move(inCard));
}
