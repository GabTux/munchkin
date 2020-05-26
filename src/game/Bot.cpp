#include "Bot.h"

Bot::Bot(std::vector<std::shared_ptr<Card>> &inHandCards, SDL_Rect &inPosition, SDLResources &inRes,
         std::shared_ptr<CardDeck> &doorDeckGarbage, std::shared_ptr<CardDeck> &treasureDeckGarbage) :
Player(inHandCards, inPosition, inRes, doorDeckGarbage, treasureDeckGarbage)
{
}

void Bot::handleEvent(SDL_Event &event)
{

}

void Bot::update(std::shared_ptr<Card> &inActCard, GameState inActState)
{
	actCard = inActCard;
	actState = inActState;

	if (!delayMillis(1000))
	{
		turnDone = false;
		return;
	}

	makeTurn();
	handCards->update();
	inventory->update();
}

bool Bot::delayMillis(int millis)
{
	static bool getTime = true;
	static Uint32 endTime;
	if (getTime)
	{
		endTime = SDL_GetTicks() + millis;
		getTime = false;
	}

	Uint32 actualTime = SDL_GetTicks();
	if (actualTime >= endTime)
	{
		getTime = true;
		return true;
	}
	return false;
}

void Bot::makeTurn()
{
	if (actState == GameState::KICK_DOORS)
	{
		if (checkForInv())
			turnDone = true;
	}

	else if (actState == GameState::FIGHT)
	{
		if (tryToDefeat())
			turnDone = true;
	}

	else if (actState == GameState::AFF_FIGHT)
	{
		turnDone = true;
	}

	else if (actState == GameState::END_TURN)
	{
		turnDone = true;
	}
}

bool Bot::played()
{
	if (turnDone)
	{
		turnDone = false;
		return true;
	}
	return false;
}

void Bot::startTurn()
{
}

bool Bot::checkForInv()
{
	for (auto& it: *handCards)
	{
		if (it->isItem())
		{
			playCard(it);
			return false;
		}
	}
	return true;
}

void Bot::playCard(std::shared_ptr<Card>& inCard)
{
	std::string helpText = "Bot played a card: ";
	helpText += inCard->getHelp();
	if (constants::infoOn) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Bot playing", helpText.c_str(), nullptr);
	inCard->markPlayed();
}

bool Bot::tryToDefeat()
{
	int monsterPower = actCard->combatPower();

	if (monsterPower <= getCombatPower())
		return true;

	int possibleBoost = 0;
	for (auto& it: *handCards)
	{
		if (it->isBoost())
			possibleBoost += it->getValue();
	}

	if (possibleBoost+getCombatPower() > monsterPower)
	{
		for (auto& it: *handCards)
			if (it->isBoost())
			{
				playCard(it);
				return false;
			}
	}

	return true;
}

bool Bot::endTurn(std::string &inString)
{
	if (handCards->getValue() <= constants::maxHandCards)
		return true;

	playCurses(handCards->getValue()-constants::maxHandCards);

	while (handCards->getValue() > constants::maxHandCards)
	{
		loseCards(1);
		handCards->updateValue();
	}

	return true;
}

void Bot::endTurn()
{
}

void Bot::playCurses(int max)
{
	int i = 0;
	for (auto& it: *handCards)
	{
		if (it->isCurse())
		{
			playCard(it);
			i++;
		}
		if (i == max)
			return;
	}
}
