#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
/**
 * Class for used SDL resources.
 */
class SDLResources
{
	public:
		SDL_Window* mainWindow = nullptr;
		SDL_Renderer* mainRenderer = nullptr;
		TTF_Font* menuFont = nullptr;
		Mix_Music* menuMusic = nullptr;
		const int windowWidth = 1200;
		const int windowHeight = 900;
};

