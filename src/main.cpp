#include <iostream>
#include <exception>
#include <typeinfo>
#include <stdexcept>

#include "scene/SDLResources.h"
#include "scene/SceneManager.h"
#include "scene/Start.h"
#include "scene/Stop.h"
#include "scene/Menu/MainMenu.h"
#include "scene/SoloGame/SoloGame.h"
#include "scene/Menu/GameMenu.h"
#include "scene/About.h"

int main()
{
	SDLResources resources;
	SceneManager sceneManager(resources);

	try
	{
		sceneManager.newScene(SceneName::START, new Start(resources, sceneManager));
		sceneManager.newScene(SceneName::STOP, new Stop(resources, sceneManager));
		sceneManager.newScene(SceneName::ABOUT, new About(resources, sceneManager));
		sceneManager.newScene(SceneName::MAIN_MENU, new MainMenu(resources, sceneManager));
		sceneManager.newScene(SceneName::GAME_MENU, new GameMenu(resources, sceneManager));
		sceneManager.newScene(SceneName::SOLO_GAME, new SoloGame(resources, sceneManager));

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
		std::cout << "Unknown exception, possibly memory corruption, exiting: ";
		std::exception_ptr pExcpt = std::current_exception();
		std::cout << pExcpt.__cxa_exception_type()->name() << std::endl;
		sceneManager.switchScene(SceneName::STOP);
	}
}