#pragma once

#include <vector>
#include <memory>

#include "cards/Card.h"
#include "PileCard.h"
#include "HandCards.h"
#include "Inventory.h"
#include "Player.h"

class Human : public Player
{
	private:


	public:
		/**
		 * Construct new human player.
		 * @param inHandCards Starting cards in hands.
		 * @param inPosition Position of player.
		 */
		Human(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition);

		/**
		 * React to user input.
		 * @param event Caught event.
		 */
		void handleEvent(SDL_Event& event) override;

		/**
		 * Update Inventory and cards in hands.
		 */
		void update() override;

		/**
		 * Render cards in hands and inventory.
		 * @param renderer Where to render.
		 */
		void render(SDL_Renderer* renderer) override;

		/**
		 * Get position of player.
		 * @return Position.
		 */
		[[nodiscard]] SDL_Rect getPosition() override { return position; };

		~Human();
};