#pragma once

#include "SoloGame1v1.h"

/**
 * Class for loading multiplayer game.
 */
class SoloGameLoad1v1 : public SoloGame1v1
{
	public:
		/**
		 * Constructs new loaded game.
		 * @param inRes Reference to SDL resources.
		 * @param inSceneManager Reference to scene manager.
		 */
		SoloGameLoad1v1(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Try to load game.
		 */
		void setStartingState() override;
};