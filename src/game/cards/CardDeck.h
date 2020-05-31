#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "Card.h"
#include "../../functions.h"

/**
 * Wrapper around vector for card decks.
 */
class CardDeck
{
	private:
		std::vector<std::shared_ptr<Card>> cards;
		std::unordered_map<int, std::shared_ptr<Card>> allCardMap;
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

		bool getCard(int id, std::shared_ptr<Card>& outCard);

		int countCards() { return cards.size(); }

		void setDefault();

		bool empty() { return cards.empty(); }

		friend std::ostream& operator<<(std::ostream& os, const CardDeck& inDeck);
};

std::ostream &operator<<(std::ostream& os, const CardDeck &inDeck);