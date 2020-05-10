#pragma once

#include "Card.h"

/**
 * Type of card - Item.
 * It can in inventory, where it gives combat bonus, or in hand.
 */
class ItemCard : public Card
{
	private:
		int combatBonus;

	public:
		/**
		 *
		 * @param fileName @see Card.h
		 * @param pos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inCombatBonus how much bonus this card will provide.
		 */
		ItemCard(const char *fileName, SDL_Rect &pos, std::string& inHelpText, int inCombatBonus);

		/**
		 * @return combat bonus provided.
		 */
		[[nodiscard]] int getValue() const override { return combatBonus; };
};