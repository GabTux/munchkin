#include "ItemCard.h"

ItemCard::ItemCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText, int inCombatBonus, TTF_Font* inFont) :
Card(fileName, pos, inHelpText, inFont), combatBonus(inCombatBonus)
{
}

bool ItemCard::play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc)
{
	if (actState != GameState::KICK_DOORS && actState != GameState::END_TURN && !inInv)
	{
		ruleDesc = "You can not put things to inventory during fights.";
		return false;
	}

	if (inInv)
	{
		ruleDesc = "Do you want to throw it away?";
		return false;
	}
	else
	{
		cardState = CardState::MOVED;
		inInv = true;
		return true;
	}
}

void ItemCard::throwAway()
{
	inInv = false;
}
