#pragma once

#include "SoloGame.h"

class SoloGame1v1 : public SoloGame
{
	private:
		void looseAgainstMonster() override;

		void checkForWinner() override;

	public:
		SoloGame1v1(SDLResources& inRes, SceneManager& inSceneManager);

		void prepare() override;

		void handleEvent() override;
};