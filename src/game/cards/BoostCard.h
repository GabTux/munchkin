#pragma once

#include "Card.h"
#include "../Player.h"

/**
 * Type of card - boost.
 * Can be played during fight - adds bonus to any side.
 */
class BoostCard : public Card
{
	private:
		int combatBonus;

	public:
		/**
		 *
		 * @param fileName @see Card.h
		 * @param inPos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inCombatBonus How much bonus it adds.
		 */
		BoostCard(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText, int inCombatBonus, TTF_Font* inFont);

		/**
		 * @return Get value of bonus.
		 */
		[[nodiscard]] int getValue() const override { return combatBonus; };

		bool play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc) override;
};