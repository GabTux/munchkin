#include "Background.h"

Background::Background(const char * const wallpaperPath) : surfaceBackground(IMG_Load(wallpaperPath))
{
	if (!surfaceBackground)
	{
		std::string message = "Unable to create background: "; message += SDL_GetError();
		throw SDLError(message);
	}
}

Background::~Background()
{
	SDL_FreeSurface(surfaceBackground);
}

void Background::update()
{

}

void Background::render(SDL_Renderer* renderer)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceBackground);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
}
