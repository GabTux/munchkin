#include "GameMenu.h"

GameMenu::GameMenu(SDLResources &res, SceneManager &sceneManager) : Menu(res, sceneManager)
{

}

void GameMenu::prepare()
{
	mainBackground = std::make_unique<Background>(constants::menuWallpaperPath);
	SceneName scenes[] = { SceneName::SOLO_GAME, SceneName::SOLO_GAME, SceneName::SOLO_GAME, SceneName::MAIN_MENU };
	SDL_Rect selectorPos = {constants::mainMenuButtonsX - constants::mainMenuSelectorSpace,
												 constants::mainMenuButtonsY[0], constants::mainMenuSelectorWidth, constants::mainMenuSelectorHeight };
	SDL_Rect buttonPos = { constants::mainMenuButtonsX, constants::mainMenuButtonsY[0], 0, 0 };
	int len = std::size(constants::gameMenuButtonsText);

	for (int i = 0; i < len; i++)
	{
		selectorPos.y = constants::mainMenuButtonsY[i];
		buttonPos.y = constants::mainMenuButtonsY[i];
		mapMenuItems[std::make_unique<MenuButton>(constants::gameMenuButtonsText[i], buttonPos, res.menuFont, scenes[i])]
						= std::make_unique<MenuSelector>(constants::menuSelectorPath, selectorPos);
	}
}

void GameMenu::render()
{
	mainBackground->render(res.mainRenderer);
	Menu::render();
}

void GameMenu::dispose()
{
	mapMenuItems.clear();
	mainBackground.reset();
}
