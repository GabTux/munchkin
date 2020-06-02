#pragma once

#include <vector>
#include <memory>

#include "cards/Card.h"
#include "GameButton.h"
#include "../functions.h"
#include "../scene/SoloGame/GameState.h"
#include "cards/CardDeck.h"

/**
 * All piles states.
 */
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
		std::unique_ptr<GameButton> arrowLeft;
		std::unique_ptr<GameButton> arrowRight;
		unsigned int showCards = 3;
		std::weak_ptr<Player> owner;
		std::weak_ptr<Player> opponent;
		std::shared_ptr<Card> actCard = nullptr;
		GameState actState = GameState::KICK_DOORS;
		std::shared_ptr<CardDeck> doorDeckGarbage;
		std::shared_ptr<CardDeck> treasureDeckGarbage;

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

		/**
		 * Show information, that this card can't be played right now.
		 * @param inMessage Description.
		 * @return Id of pressed button.
		 */
		static int cantPlayDialog(std::string& inMessage);

		/**
		 * Check if any cards were played.
		 */
		void checkForPlayedCards();

		/**
		 * Handle if card is being played.
		 * @param cardInx Actual index of card, that is being played.
		 */
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

		PileState pileState = PileState::PACKED;
		std::unique_ptr<GameButton> switchButton;

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
						SDL_Rect& inButtonPos, SDL_Rect& inPilePos, TTF_Font* menuFont, std::shared_ptr<CardDeck>& inDoorDeckGarbage, std::shared_ptr<CardDeck>& inTreasureDeckGarbage);

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

		/**
		 * Set to default state.
		 */
		void setDefault() override;

		/**
		 * Add card to pile.
		 * @param inCard New card.
		 */
		void addCard(const std::shared_ptr<Card>& inCard);

		/**
		 * Pack actual pile if it is unpacked.
		 */
		void pack();

		/**
		 * Unpack pile, if it is packed.
		 */
		void unpack();

		/**
		 * Get value of pile.
		 * For hand cards it is how many cards in hands.
		 * For inventory it is power bonus in combat power.
		 * @return Value of pile
		 */
		int getValue();

		/**
		 * Update all indicator, that shows value.
		 */
		void updateIndicator();

		/**
		 * Set players, owner and opponent.
		 * @param inOwner Owner of pile.
		 * @param inOpponent Opponent of owner.
		 */
		void setPlayers(std::shared_ptr<Player> inOwner, std::shared_ptr<Player> inOpponent);

		/**
		 * Get random card from pile.
		 * @return shared_ptr to that card.
		 */
		std::shared_ptr<Card> getRandomCard();

		/**
		 * Get iterator to begin of cards.
		 * @return Iterator to begin
		 */
		std::vector<std::shared_ptr<Card>>::iterator begin() { return cards.begin(); }

		/**
		 * Get iterator to end of cards.
		 * @return Iterator to end
		 */
		std::vector<std::shared_ptr<Card>>::iterator end() { return cards.end(); }

		/**
		 * Erase card on position.
		 * @param inIter Which card erase.
		 * @return iterator to next card.
		 */
		std::vector<std::shared_ptr<Card>>::iterator erase(std::vector<std::shared_ptr<Card>>::iterator inIter) { return cards.erase(inIter); }

		/**
		 * Encrypt data and write them to stream.
		 * @param os Target stream.
		 * @param inPileCard actual object.
		 * @return Target stream
		 */
		friend std::ostream& operator<<(std::ostream& os, const PileCard& inPileCard);
};

std::ostream& operator<<(std::ostream& os, const PileCard& inPileCard);