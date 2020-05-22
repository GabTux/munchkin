#include "HandCards.h"

HandCards::HandCards(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect &buttonPos, SDL_Rect &pilePos, TTF_Font* inFont) :
PileCard("HAND", "BACK", inCards, buttonPos, pilePos, inFont)
{
}
