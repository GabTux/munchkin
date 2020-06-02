#pragma once

#include "SoloGame.h"

/**
 * Class for handling multiplayer.
 */
class SoloGame1v1 : public SoloGame
{
	private:
		/**
		 * update information messages.
		 */
		void looseAgainstMonster() override;

		/**
		 * update information messages.
		 */
		void checkForWinner() override;

	public:
		/**
		 * Create new scene for multiplayer.
		 * @param inRes Reference to SDL Resources.
		 * @param inSceneManager Reference to scene manager.
		 */
		SoloGame1v1(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Prepare two players.
		 */
		void prepare() override;

		/**
		 * Handle all user input.
		 */
		void handleEvent() override;
};