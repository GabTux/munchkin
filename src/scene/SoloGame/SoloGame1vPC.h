#pragma once

#include "SoloGame.h"

/**
 * Class for playing vs PC.
 */
class SoloGame1vPC : public SoloGame
{
	private:
		/**
		 * Check for winner, show nice message.
		 */
		void checkForWinner() override;

		/**
		 * Update information messages.
		 */
		void looseAgainstMonster() override;

	public:
		SoloGame1vPC(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Prepare bot vs player.
		 */
		void prepare() override;

		/**
		 * Do not handle user input on action button, if is bot on turn.
		 */
		void handleEvent() override;

		/**
		 * If bot played, handle it.
		 */
		void update() override;
};