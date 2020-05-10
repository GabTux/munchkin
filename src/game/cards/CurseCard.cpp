#include "CurseCard.h"

CurseCard::CurseCard(const char *const fileName, SDL_Rect &inPos, std::string &inHelpText, int inLoseLevel) :
Card(fileName, inPos, inHelpText), loseLevel(inLoseLevel)
{

}
