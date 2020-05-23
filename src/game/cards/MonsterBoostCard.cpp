#include "MonsterBoostCard.h"

MonsterBoostCard::MonsterBoostCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText, int inBoostNum, TTF_Font* inFont) :
Card(fileName, pos, inHelpText, inFont), boostNum(inBoostNum)
{
}

bool MonsterBoostCard::play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc)
{
	if (actState != GameState::AFF_FIGHT && actState != GameState::FIGHT)
	{
		ruleDesc += "You can boost monster only just before fight (opponents or yours).";
		return false;
	}
	actCard->boostLevel(boostNum);
	return true;
}