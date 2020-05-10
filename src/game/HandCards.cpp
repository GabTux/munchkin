#include "HandCards.h"

HandCards::HandCards(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect &buttonPos, SDL_Rect &pilePos) :
PileCard("HAND", "BACK", inCards, buttonPos, pilePos)
{
}
