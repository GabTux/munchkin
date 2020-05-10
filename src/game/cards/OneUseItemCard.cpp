#include "OneUseItemCard.h"

OneUseItemCard::OneUseItemCard(const char *const fileName, SDL_Rect &inPos, std::string &inHelpText, int inCombatBonus) :
Card(fileName, inPos, inHelpText), combatBonus(inCombatBonus)
{
}
