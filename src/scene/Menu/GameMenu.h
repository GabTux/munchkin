#pragma once

#include "Menu.h"
#include "../Background.h"

/**
 * Class for game menu.
 */
class GameMenu : public Menu
{
	private:
		std::unique_ptr<Background> mainBackground;

	public:
		/**
		 * Constructs new game menu.
		 * @param res Reference to SDL resources.
		 * @param sceneManager Reference to scene manager.
		 */
		GameMenu(SDLResources& res, SceneManager& sceneManager);

		/**
		 * Prepare game menu.
		 * Add buttons and selectors.
		 */
		void prepare() override;

		/**
		 * Render background and all items.
		 */
		void render() override;
};