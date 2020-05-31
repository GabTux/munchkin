#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

#include "../Scene.h"
#include "../Background.h"
#include "../SDLResources.h"
#include "../SceneManager.h"
#include "../../constants.h"
#include "../../game/cards/Card.h"
#include "../../game/Human.h"
#include "../../Exceptions.h"
#include "../../game/cards/CardDeck.h"
#include "../../game/cards/CurseCard.h"
#include "../../game/cards/MonsterBoostCard.h"
#include "../../game/cards/MonsterCard.h"
#include "../../game/cards/LevelUpCard.h"
#include "../../game/cards/BoostCard.h"

/**
 * Scene for game.
 */
class SoloGame : public Scene
{
	private:
		GameState gameStateArr[4] = { GameState::KICK_DOORS, GameState::AFF_FIGHT, GameState::FIGHT, GameState::END_TURN };
		std::unique_ptr<Background> gameBackground;
		std::unique_ptr<CardDeck> treasureCardDeck;
		std::unique_ptr<CardDeck> treasureCardDeckBack;
		std::unique_ptr<CardDeck> doorCardDeck;
		std::unique_ptr<CardDeck> doorCardDeckBack;
		std::unique_ptr<GameButton> pauseButton;
		std::unique_ptr<Text> monsterLevelInd;
		int actStateInx = 0;
		std::shared_ptr<Card> actPlayCard = nullptr;


		/**
		 * Read all cards from file.
		 * @param fileName path to txt file with list of cards.
		 */
		void readCards(const char * const fileName);

		/**
		 * Read help text from file.
		 * @param cardFile Reference to file stream.
		 * @param helpText Reference to result vector.
		 */
		static void readHelp(std::ifstream& cardFile, std::string& helpText);

		/**
		 * Create small popup window, with buttons.
		 * @return Pressed button ID.
		 */
		static int pauseMenu();

		void getRandomCards(std::unique_ptr<CardDeck>& inCards, std::vector<std::shared_ptr<Card>>& outCards, int count);

		void handleFight();

		void kickDoor();

		void handleKicked();

		bool switchPlayer(std::string& cantEndTurn);

		bool saveToFile();

		void handlePauseMenu();

	protected:
		SceneManager& sceneManager;
		SDLResources& res;
		std::vector<std::shared_ptr<Player>> players;
		std::shared_ptr<CardDeck> doorDeckGarbage;
		std::shared_ptr<CardDeck> treasureDeckGarbage;
		bool againstBot = false;

		virtual void setStartingState();

		int actPlayerInx = 0;
		std::unique_ptr<GameButton> actionButton;
		bool stopped = false;

		void handleActionButtonPress();

		virtual void looseAgainstMonster() = 0;

		void runAway(const char *  ranAway, const char * noRanAway);

		static int dialogWin(const SDL_MessageBoxButtonData buttons[], int size, const char* title, const char* message);

		int winMenu(const char * text) const;

		virtual void checkForWinner() = 0;

		bool loadFromFile(std::ifstream& inFile, std::string& errMess);

		bool loadPlayers(std::ifstream& inFile, std::string& errMess);

		bool moveCard(char deckID, int idCard, std::shared_ptr<Card>& outCard, std::string& errMess);

		bool loadGarbageDecks(std::ifstream& inFile, std::string& errMess);

	public:
		/**
		 * Construct game scene.
		 * @param inRes reference to used SDL resources.
		 * @param inSceneManager reference to scene manager.
		 */
		SoloGame(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Init all used content.
		 */
		void prepare() override;

		/**
		 * Handle user input.
		 */
		void handleEvent() override { }

		void handleEvent(SDL_Event& event);

		/**
		 * Update players and pause button.
		 */
		void update() override;

		/**
		 * Render actual game status.
		 */
		void render() override;

		/**
		 * Reset players and cards.
		 */
		void restart() override;

		void stopScene() override;
};
