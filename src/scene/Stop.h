#pragma once

#include "SDLResources.h"
#include "SceneManager.h"

class Stop : public Scene
{
	private:
		SDLResources& res;
		SceneManager& sceneManager;
	public:
		Stop(SDLResources& inRes, SceneManager& inSceneManager);
		void prepare() override;
		void update() override;
};

