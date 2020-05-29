#pragma once

#include "PileCard.h"

class HandCards : public PileCard
{
	public:
		/**
		 * Construct new hand cards.
		 * @param inCards Starting cards.
		 * @param buttonPos Position of switch button.
		 * @param pilePos Position of pile, when it is unpacked.
		 */
		HandCards(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect& buttonPos, SDL_Rect& pilePos, TTF_Font* inFont,
						std::shared_ptr<CardDeck>& doorDeckGarbage, std::shared_ptr<CardDeck>& treasureDeckGarbage);

		/**
		 * Get count of cards.
		 */
		void updateValue() override;
};