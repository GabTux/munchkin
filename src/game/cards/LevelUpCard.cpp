#include "LevelUpCard.h"

LevelUpCard::LevelUpCard(const char *const fileName, SDL_Rect &inPos, std::string &inHelpText, int inLevel) :
Card(fileName, inPos, inHelpText), level(inLevel)
{
}
