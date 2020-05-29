#pragma once

#include "Card.h"
#include "MonsterCard.h"

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
		MonsterBoostCard(const char *const fileName, SDL_Rect &pos, std::string& inHelpText, int inPower, TTF_Font* inFont);

		/**
		 * @return boost value.
		 */
		[[nodiscard]] int getValue() const override { return boostNum; };

		bool play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc) override;

		bool isTreasure() override { return false; }

		bool isMonsterBoost() override { return true; }
};