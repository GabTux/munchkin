#pragma once

#include "Card.h"
#include "../Player.h"

/**
 * Type of card - Item.
 * It can in inventory, where it gives combat bonus, or in hand.
 */
class ItemCard : public Card
{
	private:
		int combatBonus;
		bool inInv = false;

	public:
		/**
		 *
		 * @param fileName @see Card.h
		 * @param pos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inCombatBonus how much bonus this card will provide.
		 */
		ItemCard(const char *fileName, SDL_Rect &pos, std::string& inHelpText, int inCombatBonus, TTF_Font* inFont);

		/**
		 * @return combat bonus provided.
		 */
		[[nodiscard]] int getValue() const override { return combatBonus; };

		bool play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc) override;

		void throwAway() override;

		bool isTreasure() override { return true; }

		bool isItem() override { return true; }
};