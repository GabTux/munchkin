#include "SceneManager.h"

SceneManager::~SceneManager()
{
	if (actualScene) actualScene->dispose();
}

void SceneManager::newScene(SceneName inName, Scene *inScene)
{
	sceneMap[inName] = std::shared_ptr<Scene>(inScene);
}

void SceneManager::switchScene(SceneName inName)
{
	if (actualScene) actualScene->dispose();
	actualScene = sceneMap[inName];
	actualScene->prepare();
}

void SceneManager::run()
{
	Uint32 startTime, frameTime;
	while (actualScene)
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

void SceneManager::finish()
{
	if (actualScene) actualScene->dispose();
	actualScene = nullptr;
}

