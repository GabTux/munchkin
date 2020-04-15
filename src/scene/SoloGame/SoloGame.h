#pragma once

#include "../Scene.h"
#include "../Background.h"
#include "../SDLResources.h"
#include "../SceneManager.h"
#include "../../constants.h"

class SoloGame : public Scene
{
	private:
		std::unique_ptr<Background> gameBackground;
		SDLResources& res;
		SceneManager& sceneManager;

	public:
		SoloGame(SDLResources& inRes, SceneManager& inSceneManager);
		void prepare() override;
		void render() override;
		void handleEvent() override;
};
