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
	while (actualScene)
	{
		SDL_RenderClear(res.mainRenderer);

		actualScene->handleEvent();
		if (actualScene) actualScene->update();
		if (actualScene) actualScene->render();

		SDL_RenderPresent(res.mainRenderer);
	}
}

void SceneManager::finish()
{
	if (actualScene) actualScene->dispose();
	actualScene = nullptr;
}

