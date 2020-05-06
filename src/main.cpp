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
	try
	{
		SDLResources resources;
		SceneManager sceneManager(resources);

		sceneManager.newScene(SceneName::START, new Start(resources, sceneManager));
		sceneManager.newScene(SceneName::STOP, new Stop(resources, sceneManager));
		sceneManager.newScene(SceneName::ABOUT, new About(resources, sceneManager));
		sceneManager.newScene(SceneName::MAIN_MENU, new MainMenu(resources, sceneManager));
		sceneManager.newScene(SceneName::GAME_MENU, new GameMenu(resources, sceneManager));
		sceneManager.newScene(SceneName::SOLO_GAME, new SoloGame(resources, sceneManager));

		sceneManager.switchScene(SceneName::START);
		sceneManager.run();
	}

	/* TODO:
	catch (const std::myException& excpt)
	{
		std::cout << "standard exception: " << excpt.what() << std::endl;
	}
	*/

	catch (const std::exception& excpt)
	{
		std::cout << "standard exception: " << excpt.what() << std::endl;
	}

	catch (...)
	{
		std::cout << "unhandled exception: ";
		std::exception_ptr pExcpt = std::current_exception();
		std::cout << pExcpt.__cxa_exception_type()->name() << std::endl;
	}
}