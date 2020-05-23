#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

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
		GameState gameStateArr[3] = { GameState::KICK_DOORS, GameState::FIGHT, GameState::END_TURN };
		int actStateInx = 0;
		std::unique_ptr<Background> gameBackground;
		SDLResources& res;
		SceneManager& sceneManager;
		std::unique_ptr<CardDeck> treasureCardDeck;
		std::unique_ptr<CardDeck> treasureCardDeckBack;
		std::unique_ptr<CardDeck> doorCardDeck;
		std::unique_ptr<CardDeck> doorCardDeckBack;
		std::vector<std::shared_ptr<Player>> players;
		int actPlayerInx = 0;
		std::unique_ptr<GameButton> pauseButton;
		std::unique_ptr<GameButton> actionButton;
		std::unique_ptr<Text> monsterLevelInd;

		std::shared_ptr<Card> actPlayCard = nullptr;

		bool stopped = false;


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


		static int dialogWin(const SDL_MessageBoxButtonData buttons[], int size, const char* title, const char* message);

		/**
		 * Create small popup window, with buttons.
		 * @return Pressed button ID.
		 */
		static int pauseMenu();

		static void getRandomCards(std::unique_ptr<CardDeck>& inCards, std::vector<std::shared_ptr<Card>>& outCards, int count);

		void handleFight();

		void runAway();

		void handleActionButtonPress();

		int winMenu();

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
		void handleEvent() override;

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

		void kickDoor();

		void handleKicked();

		void setRandomPlayerCards();

		void switchPlayer();
};
