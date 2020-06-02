#pragma once

#include <filesystem>

#include "../SceneManager.h"
#include "Menu.h"
#include "../Background.h"

class SaveMenu : public Menu
{
	private:
		std::unique_ptr<Background> mainBackground;

	public:
		SaveMenu(SDLResources& inRes, SceneManager& inSceneManager);

		void prepare() override;

		void render() override;

		void restart() override;
};