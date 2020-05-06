#include "About.h"

About::About(SDLResources &inRes, SceneManager &inSceneManager) : res(inRes), sceneManager(inSceneManager)
{
}

void About::prepare()
{
	mainBackground = std::make_unique<Background>(constants::aboutWallpapers[0]);
	mouthFunBackground = std::make_unique<Background>(constants::aboutWallpapers[1]);
	mouthStart = startBackTime = startSpawnTime = SDL_GetTicks();
	mouthCycles = 0;
	mouthOpen = true;
	mouthAction = false;

	SDL_Rect buttonPosition = { constants::backButtonX, constants::backButtonY, 0, 0 };
	backButton = std::make_unique<MenuButton>(constants::backButtonText, buttonPosition, res.menuFont, SceneName::MAIN_MENU);

	aboutTextPosition.x = constants::aboutTextX;
	aboutTextPosition.y = constants::aboutTextY;
	SDL_Surface *surface = TTF_RenderUTF8_Blended_Wrapped(res.menuFont, constants::aboutText, white, 1000);
	aboutTextPosition.w = surface->w;
	aboutTextPosition.h = surface->h;
	aboutTexture = SDL_CreateTextureFromSurface(res.mainRenderer, surface);
	SDL_FreeSurface(surface);

	for (int i = 0; i < 20; i++)
		spawnFigure();

	randomizeIt();
}

void About::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			sceneManager.switchScene(SceneName::STOP);
		backButton->handleEvent(event);
	}
}

void About::update()
{
	// handle background
	if (SDL_GetTicks() > startBackTime + delayBackTime)
	{
		mouthAction = true;
		delayBackTime = randomInt(2000, 5000);
		mouthStart = SDL_GetTicks();
		startBackTime = SDL_GetTicks();
		sLaugh = Mix_LoadWAV(constants::evilLaughs[randomInt(0, std::size(constants::evilLaughs)-1)]);
		Mix_PlayChannel(-1, sLaugh, 0);
	}

	// handle spawn
	if (SDL_GetTicks() > startSpawnTime + delaySpawnTime)
	{
		randomizeIt();
		delaySpawnTime = randomInt(4000, 8000);
		startSpawnTime = SDL_GetTicks();
	}

	// handle figures move
	for (auto& it: figures)
	{
		it->position.y += it->moveY;
		it->position.x += it->moveX;
		if (it->position.y <= 0 || it->position.y + it->position.h > constants::windowHeight)
			it->moveY = -it->moveY;
		if (it->position.x <= 0 || it->position.x + it->position.w > constants::windowWidth)
			it->moveX = -it->moveX;
	}

	// handle button
	switch (backButton->buttonState)
	{
		case ButtonState::NOTHING:
			backButton->color = white;
			break;
		case ButtonState::ACTIVE:
			backButton->color = red;
			break;
		case ButtonState::PRESSED:
			backButton->color = blue;
			break;
		case ButtonState::RELEASED:
			sceneManager.switchScene(backButton->targetScene);
			return;
	}
}

void About::render()
{
	renderBackgrounds();
	for (auto & it: figures)
		it->render(res.mainRenderer);
	backButton->render(res.mainRenderer);
	SDL_RenderCopy(res.mainRenderer, aboutTexture, NULL, &aboutTextPosition);
}

void About::dispose()
{
	Mix_FreeChunk(sLaugh);
	SDL_DestroyTexture(aboutTexture);
	figures.clear();
}



void About::spawnFigure()
{
	SDL_Rect pos = { randomInt(100, constants::windowWidth-100), 3, randomInt(20, 100), randomInt(20, 100) };
	figures.push_back(std::make_unique<GameObject>(constants::menuSelectorPath, pos, randomInt(1, 7), randomInt(1, 7)));
}

void About::randomizeIt()
{
	if (figures.size() > 80)
		figures.clear();

	int rInt = randomInt(0, 6);
	if (rInt)
		for (int i = 0; i < rInt; i++)
			spawnFigure();
	else
		if (!figures.empty())
			figures.pop_back();
}

int About::randomInt(int a, int b)
{
	// prepare seed for random number
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randomIntGen(a, b);
	return randomIntGen(gen);
}

void About::renderBackgrounds()
{
	if (mouthOpen && mouthAction)
	{
		if (SDL_GetTicks() > mouthStart + mouthDelay)
		{
			mouthStart = SDL_GetTicks();
			mouthFunBackground->render(res.mainRenderer);
			mouthOpen = false;
			mouthCycles++;
			if (mouthCycles > 10)
			{
				mouthCycles = 0;
				mouthAction = false;
				Mix_FreeChunk(sLaugh);
				sLaugh = nullptr;
			}
		}
		else
			mainBackground->render(res.mainRenderer);
	}

	else if (mouthAction)
	{
		if (SDL_GetTicks() > mouthStart + mouthDelay)
		{
			mouthStart = SDL_GetTicks();
			mouthOpen = true;
			mainBackground->render(res.mainRenderer);
		}
		else
			mouthFunBackground->render(res.mainRenderer);
	}

	else
		mainBackground->render(res.mainRenderer);
}
