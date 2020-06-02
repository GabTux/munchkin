#pragma once

#include "Player.h"

/**
 * Class for handling bot.
 */
class Bot : public Player
{
	private:
		bool turnDone = false;
		std::shared_ptr<Card> actCard = nullptr;
		GameState actState = GameState::KICK_DOORS;
		std::shared_ptr<Player> opponent;
		bool getTime = true;
		Uint32 endTime;

		/**
		 * Based on actual game state, make some turn.
		 */
		void makeTurn();

		/**
		 * Non blocking function, that will delay.
		 * @param millis How long delay.
		 * @return true if delay ended, false if not.
		 */
		bool delayMillis(int millis);

		/**
		 * Calculate which card is least valuable.
		 * Than throw it away.
		 */
		void loseMinValueCard();

		/**
		 * Wrapper that informs, that bot is playing.
		 * @param inCard Which card is playing.
		 */
		void playCard(std::shared_ptr<Card>& inCard);

		/**
		 * Check if it is possible to move some cards to inventory.
		 * @return false - not checked everything, need to call it again; true - done
		 */
		bool checkForInv();

		/**
		 * Check if it is possible to boost level.
		 * @return false - not checked everything, need to call it again; true - done
		 */
		bool checkForLevelUp();

		/**
		 * Check if it possible to boost monster.
		 * @param madBoost true - maximal boost, use everything; false - boost only to reasonable power
		 * @return false - not checked everything, need to call it again; true - done
		 */
		bool boostMonster(bool madBoost);

		/**
		 * Try to defeat monster.
		 * @return false - not checked everything, need to call it again; true - done
		 */
		bool tryToDefeat();

		/**
		 * Based on situation, affect fight.
		 * @return false - not checked everything, need to call it again; true - done
		 */
		bool affectFight();

		/**
		 * End turn - play everything possible and throw cards away.
		 * @return false - not checked everything, need to call it again; true - done
		 */
		bool calcEndTurn();

		/**
		 * Overridden function from player.
		 * Only check if bot is not cheating.
		 * @param inString Description.
		 * @return true
		 */
		bool endTurn(std::string& inString) override;

		/**
		 * Search and play curse from hand.
		 * @return false - not checked everything, need to call it again; true - done
		 */
		bool playCurse();

		/**
		 * Determine if it is worthy to try to affect opponent fight.
		 * @return true - worthy, else false
		 */
		bool willHarmOpp();

		/**
		 * Calculate how much it is possible to decrease opponent level.
		 * @return possible decrease
		 */
		int possibleCurseLevel();

		/**
		 * Calculate how much it is possible to boost monster.
		 * @return possible boost to monster
		 */
		int possibleBoostMonster();

	public:
		/**
		 * Create new bot.
		 * @param inHandCards Cards in hands.
		 * @param inPosition Where to place bot.
		 * @param inRes Reference to resources.
		 * @param doorDeckGarbage pointer to door garbage deck.
		 * @param treasureDeckGarbage poniter to treasure garbage deck.
		 */
		Bot(std::vector<std::shared_ptr<Card>>& inHandCards, SDL_Rect& inPosition, SDLResources& inRes,
		std::shared_ptr<CardDeck>& doorDeckGarbage, std::shared_ptr<CardDeck>& treasureDeckGarbage);

		/**
		 * Do nothing.
		 * @param event event.
		 */
		void handleEvent(SDL_Event& event) override;

		/**
		 * Do nothing. Use other function with parameters.
		 */
		void update() override { }

		/**
		 * Delays 1s, make turn, update piles.
		 * @param inActCard actual game card.
		 * @param inActState actual game state.
		 */
		void update(std::shared_ptr<Card>& inActCard, GameState inActState) override;

		[[nodiscard]] SDL_Rect getPosition() override { return position; }

		/**
		 * Determine if bot played.
		 * @return true - bot played.
		 */
		bool played() override;

		/**
		 * set pointer to opponent.
		 * @param inOpp Pointer to opponent.
		 */
		void setOpp(std::shared_ptr<Player>& inOpp) override;

		/**
		 * Set bot to default state.
		 */
		void setDefault() override;
};