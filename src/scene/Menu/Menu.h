#pragma once

#include <vector>
#include <map>
#include "MenuButton.h"
#include "../Scene.h"
#include "../SDLResources.h"
#include "MenuSelector.h"

/**
 * Base class for menus.
 */
class Menu : public Scene
{
	protected:
		SDLResources& res;
		SceneManager& sceneManager;
		std::map<std::unique_ptr<MenuButton>, std::unique_ptr<MenuSelector>> mapMenuItems;

	public:
		/**
		 * Construct new menu.
		 * @param inRes Reference to SDL resources.
		 * @param inSceneManager Reference to scene manager.
		 */
		Menu(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Handle event for each button.
		 */
		void handleEvent() override;

		/**
		 * Render each item.
		 */
		void render() override;

		/**
		 * Update each item.
		 */
		void update() override;

		/**
		 * Clears all items.
		 */
		void dispose() override;
};
