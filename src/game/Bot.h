#pragma once

#include "Player.h"

class Bot : public Player
{
	private:
		bool turnDone = false;
		std::shared_ptr<Card> actCard = nullptr;
		GameState actState = GameState::KICK_DOORS;

		void makeTurn();

		static bool delayMillis(int millis);

		bool checkForInv();

		void playCard(std::shared_ptr<Card>& inCard);

		bool tryToDefeat();

		void endTurn() override;

		bool endTurn(std::string& inString) override;

		void playCurses(int max);

	public:
		Bot(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition, SDLResources& inRes,
		std::shared_ptr<CardDeck>& doorDeckGarbage, std::shared_ptr<CardDeck>& treasureDeckGarbage);

		void handleEvent(SDL_Event& event) override;

		void update() override { }

		void update(std::shared_ptr<Card>& inActCard, GameState inActState) override;

		[[nodiscard]] SDL_Rect getPosition() override { return position; }

		bool played() override;

		void startTurn() override;
};