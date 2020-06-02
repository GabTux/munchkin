#include "SoloGameLoad1v1.h"

SoloGameLoad1v1::SoloGameLoad1v1(SDLResources &inRes, SceneManager &inSceneManager) : SoloGame1v1(inRes, inSceneManager)
{
}

void SoloGameLoad1v1::setStartingState()
{
	std::string saveFilePath = std::filesystem::current_path().string();
	saveFilePath += "/"+std::string(constants::saveFolder) + constants::saveNames[1];
	std::ifstream saveFile(saveFilePath);
	std::string errMess = "Error loading: ";

	if (!saveFile.is_open() || !loadFromFile(saveFile, errMess))
	{
		if (!saveFile.is_open())
			errMess += "Check permissions.";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error loading.", errMess.c_str(), res.mainWindow);
		saveFile.close();
		sceneManager.switchScene(SceneName::SAVE_MENU);
		return;
	}

	saveFile.close();
	if (!saveFile.eof() && saveFile.bad())
	{
		errMess += "Cannot properly close the file. Check permissions.";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning loading.", errMess.c_str(), res.mainWindow);
	}

	players[actPlayerInx]->startTurn();
}
