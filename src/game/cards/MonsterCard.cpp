#include "MonsterCard.h"

MonsterCard::MonsterCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText,
				BadStuffType inBadStuffType, int inBadStuffVal, int inLevel, int inTreasures, int inLevelsGive, TTF_Font* inFont) :
Card(fileName, pos, inHelpText, inFont), badStuffType(inBadStuffType), badStuffVal(inBadStuffVal),
level(inLevel), treasures(inTreasures), levelsGive(inLevelsGive)
{
}

void MonsterCard::boostLevel(int num)
{
	oneTimeBoost += num;
}

bool MonsterCard::play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc)
{
	if (actState != GameState::FIGHT)
		throw GameError("Monster bad stuff played not in fight state.");

	if (badStuffType == BadStuffType::CARDS)
		affPlayer->loseCards(badStuffVal);
	else
		affPlayer->changeLevel(-badStuffVal);
	return true;
}

int MonsterCard::getLevels()
{
	return levelsGive;
}

void MonsterCard::setDefault()
{
	oneTimeBoost = 0;
	Card::setDefault();
}

int MonsterCard::getCombatPower()
{
	return level + oneTimeBoost;
}
