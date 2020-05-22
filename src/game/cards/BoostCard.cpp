#include "BoostCard.h"

BoostCard::BoostCard(const char *const fileName, SDL_Rect &inPos, std::string &inHelpText, int inCombatBonus, TTF_Font* inFont) :
Card(fileName, inPos, inHelpText, inFont), combatBonus(inCombatBonus)
{
}

bool BoostCard::play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc)
{
	if (actState != GameState::FIGHT)
	{
		ruleDesc = "This card can be played during fight, only.";
		return false;
	}
	affPlayer->boostPower(combatBonus);
	return true;
}
