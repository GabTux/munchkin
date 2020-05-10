#pragma once

#include <vector>
#include <memory>

#include "cards/Card.h"
#include "GameButton.h"

enum class PileState
{
		PACKED,
		UNPACKED,
};

/**
 * Wrapper around pile of cards.
 * It can allow to browse all held cards.
 */
class PileCard : public GraphicObject
{
	private:
		std::string textPacked;
		std::string textUnpacked;
		unsigned int renderIndex;
		SDL_Rect buttonPos;
		SDL_Rect pilePos;
		PileState pileState;
		std::unique_ptr<GameButton> switchButton;
		std::unique_ptr<GameButton> arrowLeft;
		std::unique_ptr<GameButton> arrowRight;
		unsigned int showCards = 3;
		bool firstRun = true;

		/**
		 * Render unpacked pile of cards. Show 3 cards.
		 * @param renderer Where to render.
		 */
		void renderUnpacked(SDL_Renderer* renderer);

		/**
		 * Update unpacked pile of cards.
		 * Update arrows and shown cards.
		 */
		void updateUnpacked();

		/**
		 * Handle events, if pile is unpacked.
		 * Handle events for arrows and cards.
		 * @param event Caught event.
		 */
		void handleEventUnpacked(SDL_Event& event);

	protected:
		/**
		 * Vector of cards, used in both inherited classes.
		 */
		std::vector<std::shared_ptr<Card>> cards;

		/**
		 * Value of specific pile of cards.
		 * HandCards - count of cards.
		 * Inventory - sum of combat power of all items in inventory.
		 */
		int value = 0;

	public:
		/**
		 * Construct new pile of cards.
		 * @param inTextPacked Button text, when pile is packed.
		 * @param inTextUnpacked Button text, when pile is unpacked.
		 * @param inCards Cards in pile.
		 * @param inButtonPos Position of button.
		 * @param inPilePos Position of unpacked pile.
		 */
		PileCard(std::string inTextPacked, std::string inTextUnpacked, std::vector<std::shared_ptr<Card>> &inCards,
						SDL_Rect& inButtonPos, SDL_Rect& inPilePos);

		/**
		 * Handle user input.
		 * @param event Reference to caught event.
		 */
		void handleEvent(SDL_Event & event) override;

		/**
		 * Update parameters, according to events.
		 */
		void update() override;

		/**
		 * Render object.
		 * @param renderer Reference to renderer.
		 */
		void render(SDL_Renderer* renderer) override;

		/**
		 * Get actual position of PileCard.
		 * @return Position.
		 */
		SDL_Rect getPosition() override { return pilePos; };

		/**
		 * Get actual state of PileCard.
		 * @return state (PACKED - UNPACKED).
		 */
		PileState getState() { return pileState; };

		/**
		 * Update value shown in button text.
		 */
		virtual void updateValue() = 0;
};