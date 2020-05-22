#pragma once
#include "Card.h"
#include "../Player.h"

/**
 * Type of card - monster.
 */
class MonsterCard : public Card
{
	private:
		BadStuffType badStuffType;
		int badStuffVal;
		int level;
		int treasures;
		int oneTimeBoost = 0;
		int levelsGive = 1;

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
		MonsterCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText, BadStuffType inBadStuffType, int inBadStuffVal,
						int level, int inTreasures, int inLevelsGive, TTF_Font* inFont);

		/**
		 * @return Monster level.
		 */
		[[nodiscard]] int getValue() const override { return level; };

		bool isMonster() override { return true; }

		void boostLevel(int boostNum) override;

		int getTreasures() override { return treasures; }

		int getLevels() override;

		void setDefault() override;

		int combatPower() override;

		bool play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc) override;
};