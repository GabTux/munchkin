//
// Created by gaboss on 5/10/20.
//

#include "BoostCard.h"

BoostCard::BoostCard(const char *const fileName, SDL_Rect &inPos, std::string &inHelpText, int inCombatBonus) :
Card(fileName, inPos, inHelpText), combatBonus(inCombatBonus)
{
}
