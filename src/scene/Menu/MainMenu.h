#pragma once

#include <string>
#include <memory>

#include "Menu.h"
#include "MenuSelector.h"
#include "../../constants.h"
#include "../Background.h"
#include "../SoloGame/SoloGame.h"

class MainMenu : public Menu
{
	private:
		std::unique_ptr<Background> mainBackground;

	public:
		/**
		 * Construct new main menu.
		 * @param res Reference to SDL resources.
		 * @param sceneManager Reference to scene manager.
		 */
		MainMenu(SDLResources& res, SceneManager& sceneManager);

		/**
		 * Prepare main menu.
		 * Add new buttons and corresponding selectors.
		 */
		void prepare() override;

		/**
		 * Render background and all items.
		 */
		void render() override;
};
