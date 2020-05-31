#pragma once

#include <SDL2/SDL.h>

#include "../GameObject.h"
#include "../GameButton.h"
#include "../../scene/SoloGame/GameState.h"

class Player;
class MonsterCard;

enum class BadStuffType
{
		LEVEL,
		CARDS,
};

enum class CardState
{
		NOTHING,
		PLAYED,
		MOVED,
};

/**
 * Class card.
 */
class Card : public GameObject
{
	private:
		std::string helpText;
		std::unique_ptr<GameButton> playButton;
		std::unique_ptr<GameButton> helpButton;
		bool playEnabled = true;
		bool helpEnabled = true;
		int id;
		static int cardCounter;

	protected:
		CardState cardState = CardState::NOTHING;

	public:
		/**
		 * Construct new card.
		 * @param fileName Path to bmp image.
		 * @param inPos Starting position.
		 * @param inHelpText Help text, that will be shown, if button triggered.
		 */
		Card(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText, TTF_Font* inFont);

		/**
		 * React to caught events.
		 * Handle events for buttons and for card.
		 * @param event Caught event.
		 */
		void handleEvent(SDL_Event& event) override;

		/**
		 * Update according to user input.
		 * If help button is pressed, show help.
		 */
		void update() override;

		/**
		 * Render card.
		 * @param renderer Where to render.
		 */
		void render(SDL_Renderer* renderer) override;

		/**
		 * Move card to different position.
		 * @param inPos Where to move.
		 */
		void setPosition(SDL_Rect& inPos) override;

		/**
		 * @return For each type, return specific value.
		 */
		[[nodiscard]] virtual int getValue() const = 0;

		void showHelp();

		std::string& getHelp() { return helpText; }

		virtual bool isMonster() { return false; }

		virtual bool isMonsterBoost() { return false; }

		virtual bool isCurse() { return false; }

		virtual bool isItem() { return false; }

		virtual bool isBoost() { return false; }

		virtual bool isLevelUp() { return false; }

		virtual bool play(std::shared_ptr<Player>& affPlayer, std::shared_ptr<Card>& actCard, GameState actState, std::string& ruleDesc) = 0;

		virtual void throwAway() { }

		virtual int getTreasures() { return 0; }

		void changeButtons(bool enablePlay, bool enableHelp);

		virtual int getLevels() { return 0; }

		virtual void boostLevel(int boostNum) { }

		CardState getState() { return cardState; }

		void markPlayed() { cardState = CardState::PLAYED; }

		void setDefault() override;

		virtual int getCombatPower() { return 0; }

		virtual bool isTreasure() = 0;

		virtual BadStuffType getBadStuffType() { return BadStuffType::LEVEL; }

		int getID() { return id; }

		static void resetCounter() { cardCounter = 0; }
};
