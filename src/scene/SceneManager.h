#pragma once

#include <memory>
#include <unordered_map>

#include "Scene.h"
#include "SDLResources.h"
#include "../constants.h"

class SceneManager
{
	private:
		std::shared_ptr<Scene> actualScene;
		std::unordered_map<SceneName, std::shared_ptr<Scene>> sceneMap;
		SDLResources& res;

	public:
		explicit SceneManager(SDLResources& inRes) : res(inRes) {}
		~SceneManager();
		void newScene(SceneName inName, Scene* inScene);
		void switchScene(SceneName inName);
		void run();
		void finish();
};
