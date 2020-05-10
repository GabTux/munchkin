#pragma once

#include "Card.h"

/**
 * Type of card - boost monster.
 */
class MonsterBoostCard : public Card
{
	private:
		int boostNum;

	public:
		/**
		 * Construct new boost monster card.
		 * @param fileName @see Card.h
		 * @param pos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inPower How much will be monster boost.
		 */
		MonsterBoostCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText, int inPower);

		/**
		 * @return boost value.
		 */
		[[nodiscard]] int getValue() const override { return boostNum; };
};