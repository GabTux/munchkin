#pragma once

#include <vector>
#include <memory>

#include "cards/Card.h"
#include "GameButton.h"
#include "../functions.h"
#include "../scene/SoloGame/GameState.h"

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
		PileState pileState = PileState::PACKED;
		std::unique_ptr<GameButton> switchButton;
		std::unique_ptr<GameButton> arrowLeft;
		std::unique_ptr<GameButton> arrowRight;
		unsigned int showCards = 3;
		bool firstRun = true;
		std::shared_ptr<Player> owner;
		std::shared_ptr<Player> opponent;
		std::shared_ptr<Card> actCard;
		GameState actState = GameState::KICK_DOORS;

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

		static int cantPlayDialog(std::string& inMessage);

		void handlePlayedCard(unsigned int cardInx);

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
						SDL_Rect& inButtonPos, SDL_Rect& inPilePos, TTF_Font* menuFont);

		/**
		 * Handle user input.
		 * @param event Reference to caught event.
		 */
		void handleEvent(SDL_Event & event) override;


		void update(std::shared_ptr<Card>& inActCard, GameState inActState);

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

		/**
		 * Throw away holt cards and set new cards.
		 * Vector and smart pointers will ensure no memory leaks.
		 * @param inHandCards New cards.
		 */
		void setCards(std::vector<std::shared_ptr<Card>>& inHandCards);

		void setDefault() override;

		void addCard(const std::shared_ptr<Card>& inCard);

		void pack();

		int getValue();

		void setPlayers(std::shared_ptr<Player> inOwner, std::shared_ptr<Player> inOpponent);

		std::shared_ptr<Card> getRandomCard();
};