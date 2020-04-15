#pragma once

#include <vector>
#include "MenuButton.h"
#include "../Scene.h"
#include "../SDLResources.h"

class Menu : public Scene
{
	protected:
		std::vector<std::unique_ptr<MenuButton>> menuButtons;
		SDLResources& res;
		SceneManager& sceneManager;

	public:
		Menu(SDLResources& inRes, SceneManager& inSceneManager)
		: res(inRes), sceneManager(inSceneManager) {}
		~Menu() = default;
		void prepare() override {};
		void handleEvent() override;
		void update() override;
		void render() override;
		void dispose() override;
};
