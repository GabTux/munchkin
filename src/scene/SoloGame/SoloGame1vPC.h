#pragma once

#include "SoloGame.h"

class SoloGame1vPC : public SoloGame
{
	private:
		void checkForWinner() override;

	public:
		SoloGame1vPC(SDLResources& inRes, SceneManager& inSceneManager);

		void prepare() override;

		void handleEvent() override;

		void update() override;

		void looseAgainstMonster() override;
};