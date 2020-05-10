#include "MonsterCard.h"

MonsterCard::MonsterCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText,
				BadStuffType inBadStuffType, int inBadStuffVal, int inLevel) :
Card(fileName, pos, inHelpText), badStuffType(inBadStuffType), badStuffVal(inBadStuffVal), level(inLevel)
{
}