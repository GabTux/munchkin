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

		/**
		 * Determine if card is monster.
		 * @return true
		 */
		bool isMonster() override { return true; }

		/**
		 * Determine if card is treasure.
		 * @return false.
		 */
		bool isTreasure() override { return false; }

		/**
		 * Boost monster level.
		 * @param boostNum How much boost.
		 */
		void boostLevel(int boostNum) override;

		/**
		 * Determine how much treasures this monster gives, if you defeat it.
		 * @return count of treasures
		 */
		int getTreasures() override { return treasures; }

		/**
		 * Determine how much levels this monster have.
		 * @return count of levels.
		 */
		int getLevels() override;

		/**
		 * Set it to default state.
		 */
		void setDefault() override;

		/**
		 * Calculate actual combat power.
		 * @return Value of combat power
		 */
		int getCombatPower() override;

		/**
		 * Do bad thing.
		 * @param affPlayer Pointer to affected player.
		 * @param actCard Actual card.
		 * @param actState Actual game state.
		 * @param ruleDesc Reference to string, where will be filled rules, if needed.
		 * @return
		 */
		bool play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc) override;
};