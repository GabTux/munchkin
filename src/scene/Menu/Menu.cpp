#include "Menu.h"

void Menu::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			sceneManager.switchScene(SceneName::STOP);
		for (auto &it: menuButtons)
			it->handleEvent(event);
	}
}

void Menu::render()
{
	for (auto & it: menuButtons)
		it->render(res.mainRenderer);
}

void Menu::dispose()
{
	menuButtons.clear();
}

void Menu::update()
{
	for (unsigned int i = 0; i < menuButtons.size(); i++)
		menuButtons[i]->update(sceneManager);
}
