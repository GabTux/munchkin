#include "MainMenu.h"

MainMenu::MainMenu(SDLResources& inRes, SceneManager& inSceneManager) : Menu(inRes, inSceneManager) {}

void MainMenu::prepare()
{
	mainBackground = std::make_unique<Background>(constants::menuWallpaperPath);
	SceneName scenes[] = { SceneName::GAME_MENU, SceneName::SOLO_GAME, SceneName::STOP };

	SDL_Rect selectorPos = {constants::mainMenuButtonsX - constants::mainMenuSelectorSpace,
													constants::mainMenuButtonsY[0], constants::mainMenuSelectorWidth, constants::mainMenuSelectorHeight };
	SDL_Rect buttonPos = { constants::mainMenuButtonsX, constants::mainMenuButtonsY[0], 0, 0 };
	int len = std::size(constants::mainMenuButtonsText);

	for (int i = 0; i < len; i++)
	{
		selectorPos.y = constants::mainMenuButtonsY[i];
		buttonPos.y = constants::mainMenuButtonsY[i];
		mapMenuItems[std::make_unique<MenuButton>(constants::mainMenuButtonsText[i], buttonPos, res.menuFont, scenes[i])]
						= std::make_unique<MenuSelector>(constants::menuSelectorPath, selectorPos);
	}
}

void MainMenu::render()
{
	mainBackground->render(res.mainRenderer);
	Menu::render();
}

void MainMenu::dispose()
{
	Menu::dispose();
	mainBackground.reset();
}
