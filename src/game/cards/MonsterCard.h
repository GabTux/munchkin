#pragma once
#include "Card.h"

enum class BadStuffType
{
		LEVEL,
		CARDS,
};

/**
 * Type of card - monster.
 */
class MonsterCard : public Card
{
	private:
		BadStuffType badStuffType;
		int badStuffVal;
		int level;

	public:
		/**
		 * Construct new monster card.
		 * @param fileName @see Card.h
		 * @param pos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inBadStuffType Type of bad stuff, that will happen, if player will lose.
		 * @param inBadStuffVal How many levels of cards lost.
		 * @param level Level of monster.
		 */
		MonsterCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText, BadStuffType inBadStuffType, int inBadStuffVal, int level);

		/**
		 * @return Monster level.
		 */
		[[nodiscard]] int getValue() const override { return level; };

		bool isMonster() override { return true; }
};