#include "Start.h"

Start::Start(SDLResources &inRes, SceneManager &inSceneManager) :  res(inRes), sceneManager(inSceneManager)
{
}

void Start::prepare()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::string message = "Unable to initialize SDL: "; message += SDL_GetError();
		throw SDLError(message);
	}

	if (TTF_Init() != 0)
	{
		std::string message = "Unable to initialize TTF: "; message += TTF_GetError();
		throw SDLError(message);
	}

	res.mainWindow = SDL_CreateWindow("SuperMunchkin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants::windowWidth, constants::windowHeight, SDL_WINDOW_SHOWN);
	if (!res.mainWindow)
	{
		std::string message = "Unable to create mainWindow: "; message += SDL_GetError();
		throw SDLError(message);
	}

	res.mainRenderer = SDL_CreateRenderer(res.mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!res.mainRenderer)
	{
		std::string message = "Unable to create renderer: "; message += SDL_GetError();
		throw SDLError(message);
	}

	res.menuFont = TTF_OpenFont(constants::genericFontPath, constants::menuButtonTextSize);
	if (!res.menuFont)
	{
		std::string message = "Unable to load Font: "; message += TTF_GetError();
		throw TTFError(message);
	}

	res.gameFont = TTF_OpenFont(constants::genericFontPath, constants::cardButtonSize);
	if (!res.gameFont)
	{
		std::string message = "Unable to load Font: "; message += TTF_GetError();
		throw TTFError(message);
	}

	try
	{
		if (!setIcon())
		{
			std::string message = "Unable to set icon: ";
			message += SDL_GetError();
			throw SDLError(message);
		}
	}
	catch (const std::exception& excpt)
	{
		std::cout << "Error occurred, continuing program: " << excpt.what() << std::endl;
	}

	try
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
			{
				std::string message = "Unable to openAudio: ";
				message += Mix_GetError();
				throw MixError(message);
			}

			res.actualMusic = Mix_LoadMUS(constants::menuMusic);
			if (!res.actualMusic)
			{
				std::string message = "Unable to load Music: ";
				message += Mix_GetError();
				throw MixError(message);
			}
			Mix_PlayMusic( res.actualMusic, -1 );
			Mix_VolumeMusic(constants::volume);
	}
	catch (const std::exception& excpt)
	{
		std::cout << "Error occurred, continuing program: " << excpt.what() << std::endl;
	}
}

bool Start::setIcon()
{
	SDL_Surface *iconSurface = IMG_Load(constants::iconPath);
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

