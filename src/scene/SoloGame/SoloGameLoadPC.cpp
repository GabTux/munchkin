#include "SoloGameLoadPC.h"

SoloGameLoadPC::SoloGameLoadPC(SDLResources &inRes, SceneManager &inSceneManager) : SoloGame1vPC(inRes, inSceneManager)
{
}

void SoloGameLoadPC::setStartingState()
{
	std::string saveFilePath = std::filesystem::current_path().string();
	saveFilePath += "/"+std::string(constants::saveFolder) + constants::saveNames[0];
	std::ifstream saveFile(saveFilePath);
	std::string errMess = "Error loading: ";

	if (!saveFile.is_open() || !loadFromFile(saveFile, errMess))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error loading.", errMess.c_str(), res.mainWindow);
		sceneManager.switchScene(SceneName::SAVE_MENU);
		saveFile.close();
		return;
	}

	saveFile.close();
	players[actPlayerInx]->startTurn();
}
