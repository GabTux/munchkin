#include "SaveMenu.h"

SaveMenu::SaveMenu(SDLResources &inRes, SceneManager &inSceneManager) : Menu(inRes, inSceneManager)
{
}

void SaveMenu::prepare()
{
	mainBackground = std::make_unique<Background>(constants::menuWallpaperPath);
	SceneName scenes[] = { SceneName::SOLO_GAME_LOAD_PC, SceneName::SOLO_GAME_LOAD_1v1, SceneName::MAIN_MENU };
	SDL_Rect selectorPos = {constants::mainMenuButtonsX - constants::mainMenuSelectorSpace,
	                        constants::mainMenuButtonsY[0], constants::mainMenuSelectorWidth, constants::mainMenuSelectorHeight };
	SDL_Rect buttonPos = { constants::mainMenuButtonsX, constants::gameMenuButtonsY[0], 0, 0 };

	int len = std::size(constants::saveNames);
	std::string saveDir = std::filesystem::current_path().string()+"/"+constants::saveFolder;
	int itemCounter = 0;
	for (int i = 0; i < len; i++)
	{
		if (std::filesystem::exists(saveDir+constants::saveNames[itemCounter]))
		{
			selectorPos.y = constants::saveMenuButtonsY[itemCounter];
			buttonPos.y = constants::saveMenuButtonsY[itemCounter];
			menuItems.push_back(std::make_unique<MenuButtonWithSelector>(constants::saveMenuButtonsText[itemCounter], sceneManager, buttonPos,
							                                                     res.menuFont, scenes[itemCounter], constants::menuSelectorPath, selectorPos));
			itemCounter++;
		}
	}
	int backButtonInx = std::size(constants::saveMenuButtonsText)-1;
	selectorPos.y = constants::saveMenuButtonsY[itemCounter];
	buttonPos.y = constants::saveMenuButtonsY[itemCounter];
	menuItems.push_back(std::make_unique<MenuButtonWithSelector>(constants::saveMenuButtonsText[backButtonInx], sceneManager, buttonPos,
	                                                             res.menuFont, scenes[backButtonInx], constants::menuSelectorPath, selectorPos));
}

void SaveMenu::render()
{
	mainBackground->render(res.mainRenderer);
	Menu::render();
}

