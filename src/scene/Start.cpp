#include "Start.h"

Start::Start(SDLResources &inRes, SceneManager &inSceneManager) :  res(inRes), sceneManager(inSceneManager)
{
}

void Start::prepare()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::string message;
		message = "Unable to initialize SDL: %s", SDL_GetError();
		throw SDLError(message);
	}

	if (TTF_Init() != 0)
	{
		std::string message;
		message = "Unable to initialize TTF: %s", TTF_GetError();
		throw SDLError(message);
	}

	res.mainWindow = SDL_CreateWindow("SuperMunchkin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants::windowWidth, constants::windowHeight, SDL_WINDOW_SHOWN);
	if (!res.mainWindow)
	{
		std::string message;
		message = "Unable to create mainWindow: %s", SDL_GetError();
		throw SDLError(message);
	}

	if (!setIcon())
	{
		std::string message;
		message = "Unable to set icon: %s", SDL_GetError();
		throw SDLError(message);
	}

	res.mainRenderer = SDL_CreateRenderer(res.mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!res.mainRenderer)
	{
		std::string message;
		message = "Unable to create renderer: %s", SDL_GetError();
		throw SDLError(message);
	}

	res.menuFont = TTF_OpenFont(constants::menuButtonFontPath, constants::menuButtonTextSize);
	if (!res.menuFont)
	{
		std::string message;
		message = "Unable to create loadFont: %s", TTF_GetError();
		throw TTFError(message);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		std::string message;
		message = "Unable to openAudio: %s", Mix_GetError();
		throw MixError(message);
	}

	res.actualMusic = Mix_LoadMUS( constants::menuMusic );
	if (!res.actualMusic)
	{
		std::string message;
		message = "Unable to load Music: %s", Mix_GetError();
		throw MixError(message);
	}

	Mix_PlayMusic( res.actualMusic, -1 );
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

