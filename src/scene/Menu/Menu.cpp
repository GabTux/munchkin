#include "Menu.h"

Menu::Menu(SDLResources &inRes, SceneManager &inSceneManager) : res(inRes), sceneManager(inSceneManager)
{
}

void Menu::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			sceneManager.switchScene(SceneName::STOP);
		for (unsigned int i = 0; i < menuItems.size(); i++)
			menuItems[i]->handleEvent(event);
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

void Menu::dispose()
{
	menuItems.clear();
}
