#include "ItemCard.h"

ItemCard::ItemCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText, int inCombatBonus) :
Card(fileName, pos, inHelpText), combatBonus(inCombatBonus)
{
}
