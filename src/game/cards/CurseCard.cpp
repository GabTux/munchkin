#include "CurseCard.h"

CurseCard::CurseCard(const char *const fileName, SDL_Rect &inPos, std::string &inHelpText, int inBadCount, TTF_Font* inFont) :
Card(fileName, inPos, inHelpText, inFont), badCount(inBadCount), badStuff(BadStuffType::LEVEL)
{

}

bool CurseCard::play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc)
{
	if (badStuff == BadStuffType::LEVEL)
		affPlayer->changeLevel(-badCount);
	else
		affPlayer->loseCards(badCount);
	return true;
}