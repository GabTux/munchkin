#pragma once

#include "GraphicObject.h"
#include "PileCard.h"
#include "HandCards.h"
#include "Inventory.h"

/**
 * Base class for players.
 */
class Player : public GraphicObject
{
	protected:
		/**
		 * Player position.
		 * Used in inherited classes - humans and bot.
		 * TODO: bot.
		 */
		SDL_Rect position;
		std::unique_ptr<PileCard> handCards;
		std::unique_ptr<PileCard> inventory;

	public:
		/**
		 * Create new player.
		 * @param inHandCards Vector of cards in hands.
		 * @param inPosition Where will be player renderer.
		 */
		Player(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition);
};