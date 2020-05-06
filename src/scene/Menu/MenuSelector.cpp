#include "MenuSelector.h"

MenuSelector::MenuSelector(const char * const fileName, SDL_Rect & inPosition) :
				selectorPosition(inPosition), selectorSurface(SDL_LoadBMP(fileName)), show(false)
{
}

void MenuSelector::render(SDL_Renderer* renderer)
{
	if (show)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, selectorSurface);
		SDL_RenderCopy(renderer, texture, NULL, &selectorPosition);
		SDL_DestroyTexture(texture);
	}
}

MenuSelector::~MenuSelector()
{
	SDL_FreeSurface(selectorSurface);
}
