#pragma once

#include "Card.h"

/**
 * Type of card - curse.
 * Opponent will lose level/levels.
 */
class CurseCard : public Card
{
	private:
		int loseLevel;

	public:
		/**
		 *
		 * @param fileName @see Card.h
		 * @param inPos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inLoseLevel How much levels will opponent lose.
		 */
		CurseCard(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText, int inLoseLevel);

		/**
		 * @return Count of lost levels.
		 */
		[[nodiscard]] int getValue() const override { return loseLevel; };
};
