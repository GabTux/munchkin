#include "CardDeck.h"

std::shared_ptr<Card> CardDeck::getCard()
{
	if (cards.empty())
	{
		std::string message = "No cards in deck.";
		throw GameError(message);
	}
	int rChoice = randomInt(0, cards.size()-1);
	std::shared_ptr<Card> res = cards[rChoice];
	cards.erase(cards.begin()+rChoice);
	return res;
}


int CardDeck::randomInt(int a, int b)
{
	// prepare seed for random number
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randomIntGen(a, b);
	return randomIntGen(gen);
}

void CardDeck::setDefault()
{
	for (auto& it: cards)
	{
		it->throwAway();
		it->setDefault();
	}
}
