#pragma once

#include <vector>
#include <random>

#include "Card.h"

/**
 * Wrapper around vector for card decks.
 */
class CardDeck
{
	private:
		std::vector<std::shared_ptr<Card>> cards;

		/**
		 * Get random int in <a, b>.
		 * @param a Lower bound.
		 * @param b Upper bound.
		 * @return Generated int.
		 */
		int randomInt(int a, int b);

	public:

		/**
		 * Simply add new card.
		 * @param inCard New card to add.
		 */
		void addCard(std::shared_ptr<Card>& inCard) { cards.push_back(inCard); };

		/**
		 * Get random card from deck.
		 * @return random card.
		 */
		std::shared_ptr<Card> getCard();
};