#include "SoloGame.h"

SoloGame::SoloGame(SDLResources& inRes, SceneManager& inSceneManager) :
res(inRes), sceneManager(inSceneManager)
{

}


void SoloGame::render()
{
	gameBackground->render(res.mainRenderer);
}

void SoloGame::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			sceneManager.switchScene(SceneName::STOP);
	}
}

void SoloGame::prepare()
{
	gameBackground = std::make_unique<Background>(constants::gameWallpaperPath);
}
