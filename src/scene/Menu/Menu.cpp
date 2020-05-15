#include "Menu.h"

Menu::Menu(SDLResources &inRes, SceneManager &inSceneManager) : res(inRes), sceneManager(inSceneManager)
{
}

void Menu::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !stopped)
	{
		if (event.type == SDL_QUIT)
		{
			sceneManager.switchScene(SceneName::STOP);
			return;
		}
		for (auto& it: menuItems)
		{
			it->handleEvent(event);
			if (stopped) break;
		}
	}
}

void Menu::render()
{
	for (auto &it: menuItems)
		it->render(res.mainRenderer);
}

void Menu::update()
{
	for (auto &it: menuItems)
		it->update();
}

void Menu::restart()
{
	stopped = false;
	for (auto& it: menuItems)
		it->setDefault();
}
