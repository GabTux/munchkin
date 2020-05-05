#include "Start.h"

Start::Start(SDLResources &inRes, SceneManager &inSceneManager) :  res(inRes), sceneManager(inSceneManager)
{
}

void Start::prepare()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		sceneManager.switchScene(SceneName::STOP);
		return;
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
		sceneManager.switchScene(SceneName::STOP);
		return;
	}

	res.mainWindow = SDL_CreateWindow("SuperMunchkin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res.windowWidth, res.windowHeight, SDL_WINDOW_SHOWN);
	if (!res.mainWindow)
	{
		SDL_Log("Unable to create mainWindow: %s", SDL_GetError());
		sceneManager.switchScene(SceneName::STOP);
		return;
	}

	if (!setIcon())
	{
		SDL_Log("Unable to create setIcon: %s", SDL_GetError());
		sceneManager.switchScene(SceneName::STOP);
		return;
	}

	res.mainRenderer = SDL_CreateRenderer(res.mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!res.mainRenderer)
	{
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		sceneManager.switchScene(SceneName::STOP);
		return;
	}

	res.menuFont = TTF_OpenFont(constants::menuButtonFontPath, constants::menuButtonTextSize);
	if (!res.menuFont)
	{
		SDL_Log("Unable to create loadFont: %s", SDL_GetError());
		sceneManager.switchScene(SceneName::STOP);
		return;
	}
}

bool Start::setIcon()
{
	SDL_Surface *iconSurface = SDL_LoadBMP(constants::iconPath);
	if (!iconSurface)
		return false;

	SDL_SetWindowIcon(res.mainWindow, iconSurface);
	SDL_FreeSurface(iconSurface);
	return true;
}

void Start::update()
{
	sceneManager.switchScene(SceneName::MAIN_MENU);
}

