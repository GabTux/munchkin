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
		bool readCards(const char * const fileName);

		/**
		 * Read help text from file.
		 * @param cardFile Reference to file stream.
		 * @param helpText Reference to result vector.
		 */
		static bool readHelp(std::ifstream& cardFile, std::string& helpText);

		/**
		 * Create small popup window, with buttons.
		 * @return Pressed button ID.
		 */
		static int pauseMenu();

		/**
		 * From given deck take some random cards.
		 * @param inCards Source deck.
		 * @param outCards Where to store cards.
		 * @param count How much cards.
		 */
		void getRandomCards(std::unique_ptr<CardDeck>& inCards, std::vector<std::shared_ptr<Card>>& outCards, int count);

		/**
		 * Calculate and handle end of fight.
		 */
		void handleFight();

		/**
		 * Handle kicking doors.
		 * The first must-do step in turn.
		 */
		void kickDoor();

		/**
		 * Do something based on kicked card.
		 */
		void handleKicked();

		/**
		 * Switch to another player, if possible.
		 * @param cantEndTurn If it is not possible, error message goes here.
		 * @return true if switched, false if not.
		 */
		bool switchPlayer(std::string& cantEndTurn);

		/**
		 * Save actual game to file.
		 * @return true if success, false if not.
		 */
		bool saveToFile();

		/**
		 * Handle user input, if game is paused.
		 */
		void handlePauseMenu();

		/**
		 * Check line in save file.
		 * Read first line, decrypt it, create hash.
		 * Read second line as hash and check if hashes are same.
		 * If success first line goes to inStream.
		 * @param inFile Source file.
		 * @param inStream Reference to output stream.
		 * @return true if success, false if not.
		 */
		static bool checkLine(std::ifstream& inFile, std::stringstream& inStream);

	protected:
		SceneManager& sceneManager;
		SDLResources& res;
		std::vector<std::shared_ptr<Player>> players;
		std::shared_ptr<CardDeck> doorDeckGarbage;
		std::shared_ptr<CardDeck> treasureDeckGarbage;
		bool againstBot = false;
		int actPlayerInx = 0;
		std::unique_ptr<GameButton> actionButton;
		bool stopped = false;

		/**
		 * set starting state for players at the begging.
		 */
		virtual void setStartingState();

		/**
		 * Handle if action button is pressed according to actual game state.
		 */
		void handleActionButtonPress();

		/**
		 * what will happen if player loose against monster.
		 * Especially which messages show.
		 */
		virtual void looseAgainstMonster() = 0;

		/**
		 * Run away from monster.
		 * @param ranAway Text to show, if actual player did ran away.
		 * @param noRanAway Text to show, if actual player did not ran away.
		 */
		void runAway(const char *  ranAway, const char * noRanAway);

		/**
		 * Pop up dialog window with buttons.
		 * @param buttons Buttons in dialog window.
		 * @param size Size of dialog window.
		 * @param title Title of that window.
		 * @param message Message to show.
		 * @return id of pressed button.
		 */
		static int dialogWin(const SDL_MessageBoxButtonData buttons[], int size, const char* title, const char* message);

		/**
		 * Show dialog menu with message that informs, who is winner.
		 * @param text What to show.
		 * @return id of pressed button.
		 */
		int winMenu(const char * text) const;

		/**
		 * Check if someone is winner.
		 */
		virtual void checkForWinner() = 0;

		/**
		 * Load game from given file.
		 * @param inFile Source file.
		 * @param errMess Description of error, if not successful.
		 * @return true if success, else false
		 */
		bool loadFromFile(std::ifstream& inFile, std::string& errMess);

		/**
		 * Load players from given file.
		 * @param inFile Source file.
		 * @param errMess Description of error, if not successful.
		 * @return true if success, else false
		 */
		bool loadPlayers(std::ifstream& inFile, std::string& errMess);

		/**
		 * Move card from deck. Used in loading from file.
		 * @param deckID 'd' for doors, 't' for treasures.
		 * @param idCard Id of desired card.
		 * @param outCard Moved card will be placed here.
		 * @param errMess Description if it is not successful.
		 * @return true if success, else false
		 */
		bool moveCard(char deckID, int idCard, std::shared_ptr<Card>& outCard, std::string& errMess);

		/**
		 * Load Garbage decks from given file.
		 * @param inFile Source file.
		 * @param errMess Description of error, if not successful.
		 * @return true if success, else false
		 */
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

		/**
		 * Handle given event.
		 * @param event Reference to event.
		 */
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

		/**
		 * Stop scene.
		 */
		void stopScene() override;
};
