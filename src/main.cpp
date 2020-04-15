#include "scene/SDLResources.h"
#include "scene/SceneManager.h"
#include "scene/Start.h"
#include "scene/Stop.h"
#include "scene/Menu/MainMenu.h"
#include "scene/SoloGame/SoloGame.h"


int main()
{
	SDLResources resources;
	SceneManager sceneManager(resources);

	sceneManager.newScene(SceneName::START, new Start(resources, sceneManager));
	sceneManager.newScene(SceneName::STOP, new Stop(resources, sceneManager));
	sceneManager.newScene(SceneName::MAIN_MENU, new MainMenu(resources, sceneManager));
	sceneManager.newScene(SceneName::SOLO_GAME, new SoloGame(resources, sceneManager));

	sceneManager.switchScene(SceneName::START);
	sceneManager.run();
}