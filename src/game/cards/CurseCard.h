#pragma once

#include "Card.h"
#include "../Player.h"

/**
 * Type of card - curse.
 * Opponent will lose levels/cards.
 */
class CurseCard : public Card
{
	private:
		int badCount;
		BadStuffType badStuff;

	public:
		/**
		 *
		 * @param fileName @see Card.h
		 * @param inPos @see Card.h
		 * @param inHelpText @see Card.h
		 * @param inLoseLevel How much levels will opponent lose.
		 */
		CurseCard(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText, int inBadCount, TTF_Font* inFont);

		/**
		 * @return Count of lost levels or cards.
		 */
		[[nodiscard]] int getValue() const override { return badCount; };

		bool isCurse() override { return true; }

		bool play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc) override;
};
