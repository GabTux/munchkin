#include <iostream>
#include <exception>
#include <typeinfo>
#include <stdexcept>

#include "scene/SDLResources.h"
#include "scene/SceneManager.h"
#include "scene/Start.h"
#include "scene/Stop.h"
#include "scene/Menu/MainMenu.h"
#include "scene/Menu/GameMenu.h"
#include "scene/About.h"
#include "scene/SoloGame/SoloGame1v1.h"
#include "scene/SoloGame/SoloGame1vPC.h"
#include "scene/Menu/SaveMenu.h"
#include "scene/SoloGame/SoloGameLoadPC.h"
#include "scene/SoloGame/SoloGameLoad1v1.h"

int main()
{
	SDLResources resources;
	SceneManager sceneManager(resources);

	try
	{
		sceneManager.newScene(SceneName::START, std::make_shared<Start>(resources, sceneManager));
		sceneManager.newScene(SceneName::STOP, std::make_shared<Stop>(resources, sceneManager));
		sceneManager.newScene(SceneName::ABOUT, std::make_shared<About>(resources, sceneManager));
		sceneManager.newScene(SceneName::MAIN_MENU, std::make_shared<MainMenu>(resources, sceneManager));
		sceneManager.newScene(SceneName::GAME_MENU, std::make_shared<GameMenu>(resources, sceneManager));
		sceneManager.newScene(SceneName::SOLO_GAME_1v1, std::make_shared<SoloGame1v1>(resources, sceneManager));
		sceneManager.newScene(SceneName::SOLO_GAME_1vPC, std::make_shared<SoloGame1vPC>(resources, sceneManager));
		sceneManager.newScene(SceneName::SAVE_MENU, std::make_shared<SaveMenu>(resources, sceneManager));
		sceneManager.newScene(SceneName::SOLO_GAME_LOAD_PC, std::make_shared<SoloGameLoadPC>(resources, sceneManager));
		sceneManager.newScene(SceneName::SOLO_GAME_LOAD_1v1, std::make_shared<SoloGameLoad1v1>(resources, sceneManager));

		sceneManager.switchScene(SceneName::START);
		sceneManager.run();
	}

	catch(const std::runtime_error& excpt)
	{
		std::cerr << "Runtime error, exiting: " << excpt.what() << std::endl;
		sceneManager.switchScene(SceneName::STOP);
	}
	catch (const std::exception& excpt)
	{
		std::cout << "Fatal error occurred, exiting: " << excpt.what() << std::endl;
		sceneManager.switchScene(SceneName::STOP);
	}
	catch (...)
	{
		std::cout << "Unknown exception, possibly memory corruption, exiting." << std::endl;
		sceneManager.switchScene(SceneName::STOP);
	}
}