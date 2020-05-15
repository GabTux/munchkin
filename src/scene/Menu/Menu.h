#pragma once

#include <vector>
#include <map>
#include "MenuButton.h"
#include "../Scene.h"
#include "../SDLResources.h"
#include "MenuSelector.h"
#include "MenuButtonWithSelector.h"

/**
 * Base class for menus.
 */
class Menu : public Scene
{
	private:
		bool stopped = false;

	protected:
		/**
		 * SDL Resources used in in inherited menus.
		 */
		SDLResources& res;

		/**
		 * Reference to sceneManager, used globally in project.
		 */
		SceneManager& sceneManager;

		/**
		 * Vector of menu items used in all inherited menus.
		 */
		std::vector<std::unique_ptr<MenuButtonWithSelector>> menuItems;

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
		 * Reset all items.
		 */
		void restart() override;

		/**
		 * Stop handling events for buttons.
		 */
		void stopScene() override { stopped = true; }
};
