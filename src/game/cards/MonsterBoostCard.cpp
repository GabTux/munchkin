#include "MonsterBoostCard.h"

MonsterBoostCard::MonsterBoostCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText, int inBoostNum) :
Card(fileName, pos, inHelpText), boostNum(inBoostNum)
{
}
