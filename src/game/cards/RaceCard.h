#pragma once

#include "Card.h"

/**
 * Special type of Card.
 * It can be only in hand on in the inventory.
 * If it is in inventory, it determines player Race.
 */
class RaceCard : public Card
{
	private:
		//TODO

	public:
		/**
		 * Create new race card.
		 * @param fileName @see Card.h
		 * @param pos @see Card.h
		 * @param inHelpText @see Card.h
		 */
		RaceCard(const char * const fileName, SDL_Rect& pos, std::string& inHelpText);

		/**
		 * Return 0, because race have no special value.
		 * @return 0.
		 */
		[[nodiscard]] int getValue() const override { return 0; };
};