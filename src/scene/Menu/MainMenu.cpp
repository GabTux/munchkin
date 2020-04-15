#include "MainMenu.h"

MainMenu::MainMenu(SDLResources& inRes, SceneManager& inSceneManager) : Menu(inRes, inSceneManager) {}

void MainMenu::prepare()
{
	mainBackground = std::make_unique<Background>(constants::menuWallpaperPath);

	SDL_Rect selectorPos = {constants::buttonsX - 70, constants::buttonsY1, 50, 65};
	SDL_Rect buttonPos = {constants::buttonsX, constants::buttonsY1, 0, 0};
	menuSelectors.push_back(std::make_unique<MenuSelector>(constants::menuSelectorPath, selectorPos));
	menuButtons.push_back(std::make_unique<MenuButton>(constants::buttonText1, buttonPos, res.menuFont, SceneName::SOLO_GAME));

	selectorPos.y = constants::buttonsY2;
	buttonPos.y = constants::buttonsY2;
	menuSelectors.push_back(std::make_unique<MenuSelector>(constants::menuSelectorPath, selectorPos));
	menuButtons.push_back(std::make_unique<MenuButton>(constants::buttonText2, buttonPos, res.menuFont, SceneName::SOLO_GAME));

	selectorPos.y = constants::buttonsY3;
	buttonPos.y = constants::buttonsY3;
	menuSelectors.push_back(std::make_unique<MenuSelector>(constants::menuSelectorPath, selectorPos));
	menuButtons.push_back(std::make_unique<MenuButton>(constants::buttonText3, buttonPos, res.menuFont, SceneName::SOLO_GAME));

	selectorPos.y = constants::buttonsY4;
	buttonPos.y = constants::buttonsY4;
	menuSelectors.push_back(std::make_unique<MenuSelector>(constants::menuSelectorPath, selectorPos));
	menuButtons.push_back(std::make_unique<MenuButton>(constants::buttonText4, buttonPos, res.menuFont, SceneName::STOP));
}

void MainMenu::render()
{
	mainBackground->render(res.mainRenderer);

	Menu::render();

	for (auto & it: menuSelectors)
		it->render(res.mainRenderer);
}

void MainMenu::update()
{
	Menu::update();
	for (unsigned int i = 0; i < menuButtons.size(); i++)
		switch (menuButtons[i]->buttonState)
		{
			case ButtonState::NOTHING:
				menuButtons[i]->color = {255, 255, 255};
				menuSelectors[i]->show = false;
				break;
			case ButtonState::ACTIVE:
				menuButtons[i]->color = {188, 26, 26};
				menuSelectors[i]->show = true;
				break;
			case ButtonState::PRESSED:
				menuButtons[i]->color = {41, 57, 201};
				break;
			case ButtonState::RELEASED:
				menuButtons[i]->color = {41, 57, 201};
				break;
		}
}

void MainMenu::dispose()
{
	Menu::dispose();
	menuSelectors.clear();
	mainBackground.reset();
}
