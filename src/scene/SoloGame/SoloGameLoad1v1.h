#pragma once

#include "SoloGame1v1.h"

class SoloGameLoad1v1 : public SoloGame1v1
{
	public:
		SoloGameLoad1v1(SDLResources& inRes, SceneManager& inSceneManager);

		void setStartingState() override;
};