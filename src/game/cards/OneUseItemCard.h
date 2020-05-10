#pragma once

#include "Card.h"

/**
 * Type of card.
 * It can be used only once in fight.
 * It can be carried in hand, but not in inventory.
 */
class OneUseItemCard : public Card
{
	private:
		int combatBonus;

	public:
		/**
		 * Create new one use card.
		 * @param fileName @see Card.h
		 * @param inPos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inCombatBonus Bonus provided in fight if card is used.
		 */
		OneUseItemCard(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText, int inCombatBonus);

		/**
		 * @return Combat bonus.
		 */
		[[nodiscard]] int getValue() const override { return combatBonus; };
};