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
	handCards->update(actCard, actState);
	inventory->update(actCard, actState);
}

bool Bot::delayMillis(int millis)
{
	if (getTime)
	{
		endTime = SDL_GetTicks() + millis;
		getTime = false;
	}

	if (SDL_GetTicks() >= endTime)
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
		if (checkForInv() && checkForLevelUp())
			turnDone = true;
	}

	else if (actState == GameState::FIGHT)
	{
		if (tryToDefeat())
			turnDone = true;
	}

	else if (actState == GameState::AFF_FIGHT)
	{
		if (affectFight())
			turnDone = true;
	}

	else if (actState == GameState::END_TURN)
	{
		if (calcEndTurn())
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
	int monsterPower = actCard->getCombatPower();

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
	if (handCards->getValue() > constants::maxHandCards)
		throw GameError("Bot have too many cards in hands, after end of turn.");

	return true;
}

void Bot::endTurn()
{
}

bool Bot::playCurse()
{
	for (auto& it: *handCards)
	{
		if (it->isCurse())
		{
			playCard(it);
			return false;
		}
	}
	return true;
}

bool Bot::affectFight()
{
	// case 1:
	// player is going to win --> use everything to stop him
	if (opponent->getLevel() + actCard->getLevels() >= constants::winLevel)
	{
		if (!boostMonster(true))
			return false;
	}

	// case 2:
	// player is most likely going to lose --> do nothing
	if (opponent->getCombatPower()+2 <= actCard->getCombatPower())
		return true;

	// case 3:
	// player is going to defeat monster, but it is maybe possible to change it
	// see if loosing against that monster will harm opponent
	// aggressive mode
	if ((opponent->getCombatPower() - possibleCurseLevel() <= actCard->getCombatPower() + possibleBoostMonster()) && willHarmOpp())
	{
		if (!boostMonster(false))
			return false;
	}

	// other cases
	return true;
}

void Bot::setOpp(std::shared_ptr<Player> &inOpp)
{
	opponent = inOpp;
	Player::setOpp(inOpp);
}

bool Bot::calcEndTurn()
{
	if (handCards->getValue() <= constants::maxHandCards)
		return true;

	if (!checkForInv())
		return false;

	if (!checkForLevelUp())
		return false;

	if (!playCurse())
		return false;

	if (constants::infoOn)
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Bot playing",
													"Bot is throwing some cards away.", nullptr);

	while (handCards->getValue() > constants::maxHandCards)
	{
		loseMinValueCard();
		handCards->updateValue();
	}
	return true;
}

void Bot::loseMinValueCard()
{
	auto min = handCards->begin();
	for (auto it = handCards->begin(); it != handCards->end(); it++)
		if (it->get()->getValue() > min->get()->getValue())
			min = it;

	handCards->erase(min);
}

bool Bot::checkForLevelUp()
{
	if (getLevel() == constants::winLevel-1)
		return true;

	for (auto& it: *handCards)
	{
		if (it->isLevelUp())
		{
			playCard(it);
			return false;
		}
	}
	return true;
}

bool Bot::boostMonster(bool madBoost)
{
	if ((actCard->getCombatPower() >= opponent->getCombatPower()) && !madBoost)
		return true;

	for (auto& it: *handCards)
	{
		if (it->isBoost() || it->isMonsterBoost())
		{
			playCard(it);
			return false;
		}
	}
	return true;
}

int Bot::possibleCurseLevel()
{
	int res = 0;

	for (auto& it: *handCards)
		if (it->isCurse() && it->getBadStuffType() == BadStuffType::LEVEL)
			res += it->getValue();

	return res;
}

int Bot::possibleBoostMonster()
{
	int res = 0;

	for (auto& it: *handCards)
		if (it->isBoost() || it->isMonsterBoost())
			res += it->getValue();

	return res;
}

bool Bot::willHarmOpp()
{
	if (actCard->getBadStuffType() == BadStuffType::CARDS && opponent->getCardsCount() < actCard->getValue()/2)
		return false;

	if (actCard->getBadStuffType() == BadStuffType::LEVEL && opponent->getLevel() == 1)
		return false;

	return true;
}

void Bot::setDefault()
{
	Player::setDefault();
	getTime = true;
}
