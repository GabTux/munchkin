#pragma once

#include <memory>
#include <unordered_map>

#include "Scene.h"
#include "SDLResources.h"
#include "../constants.h"

/**
 * Class for scene management.
 */
class SceneManager
{
	private:
		std::shared_ptr<Scene> actualScene;
		std::unordered_map<SceneName, std::shared_ptr<Scene>> sceneMap;
		SDLResources& res;
		bool running = true;

	public:
		/**
		 * Construct a new sceneManager.
		 * All scenes will be saved in sceneMap.
		 * @param inRes reference to SDL resources.
		 */
		explicit SceneManager(SDLResources& inRes) : res(inRes) {}

		/**
		 * Register new scene to map.
		 * @param inName name of new scene.
		 * @param inScene reference to new scene.
		 */
		void newScene(SceneName inName, std::shared_ptr<Scene> inScene);

		/**
		 * Switch actual scene.
		 * @param inName name of desired scene.
		 */
		void switchScene(SceneName inName);

		/**
		 * run mainloop of actual scene.
		 */
		void run();

		void stopGame() { running = false; };
};
