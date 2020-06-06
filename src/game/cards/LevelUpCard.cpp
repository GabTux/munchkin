#include "LevelUpCard.h"

LevelUpCard::LevelUpCard(const char *const fileName, SDL_Rect &inPos, std::string &inHelpText, int inLevel, TTF_Font* inFont) :
Card(fileName, inPos, inHelpText, inFont), level(inLevel)
{
}

bool LevelUpCard::play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc)
{
	if (actState == GameState::FIGHT || actState == GameState::AFF_FIGHT)
	{
		ruleDesc = "This card can not be played during fight!";
		return false;
	}

	if (affPlayer->getLevel()+level >= constants::winLevel)
	{
		ruleDesc = "Last level can be achieved by defeating monster, only.";
		return false;
	}

	affPlayer->changeLevel(level);
	return true;
}
