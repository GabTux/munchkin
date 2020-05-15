#include "SceneManager.h"

#include <utility>

void SceneManager::newScene(SceneName inName, std::shared_ptr<Scene> inScene)
{
	sceneMap[inName] = std::move(inScene);
}

void SceneManager::switchScene(SceneName inName)
{
	if (actualScene) actualScene->stopScene();
	actualScene = sceneMap[inName];
	if (actualScene->ready())
		actualScene->restart();
	else
		actualScene->makeReady();
}

void SceneManager::run()
{
	Uint32 startTime, frameTime;
	while (running && actualScene)
	{
		startTime = SDL_GetTicks();
		SDL_RenderClear(res.mainRenderer);

		actualScene->handleEvent();
		if (actualScene) actualScene->update();
		if (actualScene) actualScene->render();

		if (actualScene) SDL_RenderPresent(res.mainRenderer);

		frameTime = SDL_GetTicks() - startTime;

		if (frameTime < constants::minFrameTime)
			SDL_Delay(constants::minFrameTime-frameTime);
	}
}

