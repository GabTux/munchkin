#pragma once

#include "Card.h"

/**
 * Type of card - level up.
 * If this card is played, player will gain level/levels.
 */
class LevelUpCard : public Card
{
	private:
		int level;

	public:
		/**
		 *
		 * @param fileName @see Card.h
		 * @param inPos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inLevel How much will player gain.
		 */
		LevelUpCard(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText, int inLevel);

		/**
		 * @return levels gained.
		 */
		[[nodiscard]] int getValue() const override { return level; };
};