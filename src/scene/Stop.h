#pragma once

#include "SDLResources.h"
#include "SceneManager.h"

class Stop : public Scene
{
	private:
		SDLResources& res;
		SceneManager& sceneManager;
	public:
		/**
		 * Construct start scene.
		 * @param inRes reference to used SDL resources.
		 * @param inSceneManager reference to scene manager.
		 */
		Stop(SDLResources& inRes, SceneManager& inSceneManager);

		/*
		 * Try to clear all SDL resources.
		 */
		void prepare() override;

		/*
		 * Call the end of mainloop.
		 */
		void update() override;
};

