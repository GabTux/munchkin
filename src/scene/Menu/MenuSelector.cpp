#include "MenuSelector.h"

MenuSelector::MenuSelector(const char * const fileName, SDL_Rect & inPosition) : position(inPosition)
{
	surface = SDL_LoadBMP(fileName);
	show = false;
}

void MenuSelector::render(SDL_Renderer* renderer)
{
	if (show)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, &position);
		SDL_DestroyTexture(texture);
	}
}

MenuSelector::~MenuSelector()
{
	SDL_FreeSurface(surface);
}
