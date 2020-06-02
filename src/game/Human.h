#pragma once

#include <vector>
#include <memory>

#include "cards/Card.h"
#include "PileCard.h"
#include "HandCards.h"
#include "Inventory.h"
#include "Player.h"

/**
 * Player is human.
 */
class Human : public Player
{
	private:


	public:
		/**
		 * Construct new human player.
		 * @param inHandCards Starting cards in hands.
		 * @param inPosition Position of player.
		 */
		Human(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition, SDLResources& inRes,
					std::shared_ptr<CardDeck>& doorDeckGarbage, std::shared_ptr<CardDeck>& treasureDeckGarbage);

		/**
		 * React to user input.
		 * @param event Caught event.
		 */
		void handleEvent(SDL_Event& event) override;

		/**
		 * Do nothing - other overloaded update function with parameters will be used.
		 */
		void update() override { }

		/**
		 * Update indicators and both piles.
		 * @param inActCard actual card or nullptr.
		 * @param inActState actual game state.
		 */
		void update(std::shared_ptr<Card>& inActCard, GameState inActState) override;

		void startTurn() override;

		void endTurn() override;

		bool endTurn(std::string& inString) override;

		/**
		 * Get position of player.
		 * @return Position.
		 */
		[[nodiscard]] SDL_Rect getPosition() override { return position; };
};