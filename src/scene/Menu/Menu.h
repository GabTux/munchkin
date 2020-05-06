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
	protected:
		SDLResources& res;
		SceneManager& sceneManager;
		std::vector<std::unique_ptr<MenuButtonWithSelector>> menuItems;
		SDL_Color white = {255, 255, 255 };
		SDL_Color red = { 188, 26, 26 };
		SDL_Color blue = {41, 57, 201 };

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
