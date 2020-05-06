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
		for (auto &it: menuItems)
			it->handleEvent(event);
	}
}

void Menu::render()
{
	for (auto &it: menuItems)
	{
		it->render(res.mainRenderer);
	}
}

void Menu::update()
{
	for (auto &it: menuItems)
	{
		switch (it->buttonState)
		{
			case ButtonState::NOTHING:
				it->color = white;
				it->MenuSelector::show = false;
				break;
			case ButtonState::ACTIVE:
				it->color = red;
				it->MenuSelector::show = true;
				break;
			case ButtonState::PRESSED:
				it->color = blue;
				it->MenuSelector::show = true;
				break;
			case ButtonState::RELEASED:
				sceneManager.switchScene(it->targetScene);
				return;
		}
	}
}

void Menu::dispose()
{
	menuItems.clear();
}
