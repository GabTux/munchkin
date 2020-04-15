#pragma once

#include "Scene.h"
#include "SDLResources.h"
#include "SceneManager.h"
#include "../constants.h"

class Start : public Scene
{
	private:
		SDLResources& res;
		SceneManager& sceneManager;

		bool setIcon();

	public:
		Start(SDLResources& inRes, SceneManager& inSceneManager) : res(inRes), sceneManager(inSceneManager) {}
		void prepare() override;
		void update() override;
};
