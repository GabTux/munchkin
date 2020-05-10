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
		HandCards(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect& buttonPos, SDL_Rect& pilePos);

		/**
		 * Get count of cards.
		 */
		void updateValue() override {  value = cards.size(); };
};