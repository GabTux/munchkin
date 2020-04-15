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
		std::vector<std::unique_ptr<MenuSelector>> menuSelectors;

	public:
		MainMenu(SDLResources& res, SceneManager& sceneManager);
		void dispose() override;
		void prepare() override;
		void update() override;
		void render() override;
};
