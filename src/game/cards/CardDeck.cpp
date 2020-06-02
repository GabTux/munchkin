#include "CardDeck.h"

CardDeck::CardDeck(std::shared_ptr<CardDeck> &inRecovery) : recoveryDeck(inRecovery)
{
}

std::shared_ptr<Card> CardDeck::getCard()
{
	if (cards.empty())
	{
		if (!recoveryDeck || recoveryDeck->empty())
			throw GameError("No cards in deck.");

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
	allCardMap[inCard->getID()] = inCard;
	cards.push_back(std::move(inCard));
}

bool CardDeck::getCard(int id, std::shared_ptr<Card>& outCard)
{
	if (allCardMap.find(id) == allCardMap.end())
		return false;

	cards.erase(std::remove(cards.begin(), cards.end(), allCardMap[id]));
	outCard = allCardMap[id];
	return true;
}

std::ostream &operator<<(std::ostream& os, const CardDeck& inDeck)
{
	std::string res;
	unsigned long checkHash;


	for (auto& it: inDeck.cards)
		res += std::to_string(it->getID())+" ";
	res += "-1";

	checkSum(res, checkHash);
	encryptDecrypt(res);

	os << res << std::endl << checkHash;
	return os;
}
