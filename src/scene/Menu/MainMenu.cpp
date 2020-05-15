#include "MainMenu.h"

MainMenu::MainMenu(SDLResources& inRes, SceneManager& inSceneManager) : Menu(inRes, inSceneManager) {}

void MainMenu::prepare()
{
	mainBackground = std::make_unique<Background>(constants::menuWallpaperPath);
	SceneName scenes[] = { SceneName::GAME_MENU, SceneName::ABOUT, SceneName::STOP };

	SDL_Rect selectorPos = {constants::mainMenuButtonsX - constants::mainMenuSelectorSpace,
													constants::mainMenuButtonsY[0], constants::mainMenuSelectorWidth, constants::mainMenuSelectorHeight };
	SDL_Rect buttonPos = { constants::mainMenuButtonsX, constants::mainMenuButtonsY[0], 0, 0 };
	int len = std::size(constants::mainMenuButtonsText);

	for (int i = 0; i < len; i++)
	{
		selectorPos.y = constants::mainMenuButtonsY[i];
		buttonPos.y = constants::mainMenuButtonsY[i];
		menuItems.push_back(std::make_unique<MenuButtonWithSelector>(constants::mainMenuButtonsText[i], sceneManager, buttonPos, res.menuFont, scenes[i], constants::menuSelectorPath, selectorPos));
	}

	if (!Mix_PlayingMusic())
	{
		res.actualMusic = Mix_LoadMUS(constants::menuMusic);
		Mix_PlayMusic(res.actualMusic, -1);
	}
}

void MainMenu::render()
{
	mainBackground->render(res.mainRenderer);
	Menu::render();
}