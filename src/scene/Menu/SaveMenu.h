#pragma once

#include <filesystem>

#include "../SceneManager.h"
#include "Menu.h"
#include "../Background.h"

/**
 * Class that shows save menu.
 */
class SaveMenu : public Menu
{
	private:
		std::unique_ptr<Background> mainBackground;

	public:
		/**
		 * Create new save menu.
		 * @param inRes Reference to SDL resources.
		 * @param inSceneManager Reference to scene manager.
		 */
		SaveMenu(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Create desired buttons.
		 */
		void prepare() override;

		/**
		 * Render buttons and background.
		 */
		void render() override;

		/**
		 * Clear all buttons and prepare them again.
		 * Must-do because save files can be removed/added during running game.
		 */
		void restart() override;
};