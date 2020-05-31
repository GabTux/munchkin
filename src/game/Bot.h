#pragma once

#include "Player.h"

class Bot : public Player
{
	private:
		bool turnDone = false;
		std::shared_ptr<Card> actCard = nullptr;
		GameState actState = GameState::KICK_DOORS;
		std::shared_ptr<Player> opponent;
		bool getTime = true;
		Uint32 endTime;

		void makeTurn();

		bool delayMillis(int millis);

		void loseMinValueCard();

		void playCard(std::shared_ptr<Card>& inCard);

		bool checkForInv();

		bool checkForLevelUp();

		bool boostMonster(bool madBoost);

		bool tryToDefeat();

		bool affectFight();

		bool calcEndTurn();

		void endTurn() override;

		bool endTurn(std::string& inString) override;

		bool playCurse();

		bool willHarmOpp();

		int possibleCurseLevel();

		int possibleBoostMonster();

	public:
		Bot(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition, SDLResources& inRes,
		std::shared_ptr<CardDeck>& doorDeckGarbage, std::shared_ptr<CardDeck>& treasureDeckGarbage);

		void handleEvent(SDL_Event& event) override;

		void update() override { }

		void update(std::shared_ptr<Card>& inActCard, GameState inActState) override;

		[[nodiscard]] SDL_Rect getPosition() override { return position; }

		bool played() override;

		void startTurn() override;

		void setOpp(std::shared_ptr<Player>& inOpp) override;

		void setDefault() override;
};