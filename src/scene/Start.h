#pragma once

#include <string>

#include "Scene.h"
#include "SDLResources.h"
#include "SceneManager.h"
#include "../constants.h"
#include "../Exceptions.h"

/**
 * Prepare all used content in program. Mostly it initializes SDL.
 */
class Start : public Scene
{
	private:
		SDLResources& res;
		SceneManager& sceneManager;

		bool setIcon();

	public:
		/**
		 * Construct start scene.
		 * @param inRes SDLResources, that will be initialized.
		 * @param inSceneManager Scene manager, used to switch to another scene.
		 */
		Start(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Try to initialize SDL resources.
		 */
		void prepare() override;

		/*
		 * Switch to main menu to start the loop.
		 */
		void update() override;
};
