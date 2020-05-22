#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
/**
 * Structure for used SDL resources.
 */
struct SDLResources
{
	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* mainRenderer = nullptr;
	TTF_Font* menuFont = nullptr;
	TTF_Font* gameFont = nullptr;
	Mix_Music* actualMusic = nullptr;
};