#pragma once

#include <utility>

#include "GraphicObject.h"
#include "PileCard.h"
#include "HandCards.h"
#include "Inventory.h"
#include "Text.h"

/**
 * Base class for players.
 */
class Player : public GraphicObject, public std::enable_shared_from_this<Player>
{
	private:
		int level = 1;
		int oneTimeBoost = 0;

	protected:
		/**
		 * Player position.
		 * Used in inherited classes - humans and bot.
		 * TODO: bot.
		 */
		SDL_Rect position;
		std::unique_ptr<PileCard> handCards;
		std::unique_ptr<PileCard> inventory;
		std::unique_ptr<Text> levelIndicator;
		std::unique_ptr<Text> powerIndicator;
		SDLResources& res;
		std::shared_ptr<Player> opp;

	public:
		/**
		 * Create new player.
		 * @param inHandCards Vector of cards in hands.
		 * @param inPosition Where will be player renderer.
		 */
		Player(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition, SDLResources& inRes);

		void setHandCards(std::vector<std::shared_ptr<Card>>& inHandCards);

		void setInvCards(std::vector<std::shared_ptr<Card>>& inHandCards);

		void setDefault() override;

		void gotCard(const std::shared_ptr<Card>& inCard);

		void toInvCard(std::shared_ptr<Card>& inCard);

		bool endTurn(std::string& inString);

		void loseCards(int loseCardsNum);

		void update() override { }

		virtual void update(std::shared_ptr<Card>& inActCard, GameState inActState) = 0;

		void render(SDL_Renderer* renderer) override;

		void boostPower(int num);

		void setOpp(std::shared_ptr<Player>& inOpp);

		void changeLevel(int num);

		int getCombatPower();

		void resetBoost();

		void updateIndicators();

		int getLevel() { return level; }
};