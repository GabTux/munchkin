#pragma once

#include <vector>

#include "Card.h"
#include "../../functions.h"

/**
 * Wrapper around vector for card decks.
 */
class CardDeck
{
	private:
		std::vector<std::shared_ptr<Card>> cards;
		std::shared_ptr<CardDeck> recoveryDeck = nullptr;

	public:
		CardDeck() = default;

		explicit CardDeck(std::shared_ptr<CardDeck>& inRecovery);

		/**
		 * Simply add new card.
		 * @param inCard New card to add.
		 */
		void addCard(std::shared_ptr<Card> inCard);

		/**
		 * Get random card from deck.
		 * @return random card.
		 */
		std::shared_ptr<Card> getCard();

		int countCards() { return cards.size(); }

		void setDefault();
};