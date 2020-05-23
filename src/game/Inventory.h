#pragma once

#include "PileCard.h"
#include "cards/ItemCard.h"

class Inventory : public PileCard
{
	public:
		/**
		 * Construct new inventory.
		 * @param inCards Cards in inventory.
		 * @param buttonPos Position of button.
		 * @param pilePos Position of pile.
		 */
		Inventory(std::vector<std::shared_ptr<Card>> &inCards, SDL_Rect& buttonPos, SDL_Rect& pilePos, TTF_Font* inFont,
							std::shared_ptr<CardDeck>& inDoorDeckGarbage, std::shared_ptr<CardDeck>& inTreasureDeckGarbage);

		/**
		 * Count all combat bonuses from items.
		 */
		void updateValue() override;
};
