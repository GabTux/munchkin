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
		for (auto &it: mapMenuItems)
			it.first->handleEvent(event);
	}
}

void Menu::render()
{
	for (auto &it: mapMenuItems)
	{
		it.first->render(res.mainRenderer);
		it.second->render(res.mainRenderer);
	}
}

void Menu::update()
{
	for (auto &it: mapMenuItems)
	{
		//it.first->update(sceneManager);
		switch (it.first->buttonState)
		{
			case ButtonState::NOTHING:
				it.first->color = {255, 255, 255};
				it.second->show = false;
				break;
			case ButtonState::ACTIVE:
				it.first->color = {188, 26, 26};
				it.second->show = true;
				break;
			case ButtonState::PRESSED:
				it.first->color = {41, 57, 201};
				break;
			case ButtonState::RELEASED:
				it.first->color = {41, 57, 201};
				sceneManager.switchScene(it.first->targetScene);
				return;
		}
	}
}

void Menu::dispose()
{
	mapMenuItems.clear();
}
