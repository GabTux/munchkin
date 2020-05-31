#include "GameMenu.h"

GameMenu::GameMenu(SDLResources &res, SceneManager &sceneManager) : Menu(res, sceneManager)
{

}

void GameMenu::prepare()
{
	mainBackground = std::make_unique<Background>(constants::menuWallpaperPath);
	SceneName scenes[] = { SceneName::SOLO_GAME_1vPC, SceneName::SOLO_GAME_1v1, SceneName::SAVE_MENU, SceneName::MAIN_MENU };
	SDL_Rect selectorPos = {constants::mainMenuButtonsX - constants::mainMenuSelectorSpace,
												 constants::mainMenuButtonsY[0], constants::mainMenuSelectorWidth, constants::mainMenuSelectorHeight };
	SDL_Rect buttonPos = { constants::mainMenuButtonsX, constants::gameMenuButtonsY[0], 0, 0 };
	int len = std::size(constants::gameMenuButtonsText);

	for (int i = 0; i < len; i++)
	{
		selectorPos.y = constants::gameMenuButtonsY[i];
		buttonPos.y = constants::gameMenuButtonsY[i];
		menuItems.push_back(std::make_unique<MenuButtonWithSelector>(constants::gameMenuButtonsText[i], sceneManager, buttonPos, res.menuFont, scenes[i], constants::menuSelectorPath, selectorPos));
	}
}

void GameMenu::render()
{
	mainBackground->render(res.mainRenderer);
	Menu::render();
}
