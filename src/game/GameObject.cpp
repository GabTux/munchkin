#include "GameObject.h"

GameObject::GameObject(const char * const fileName, SDL_Rect & inPosition, int inMoveX, int inMoveY) :
surface(SDL_LoadBMP(fileName)), position(inPosition), moveX(inMoveX), moveY(inMoveY)
{
	if (!surface)
	{
		std::string message = "Unable to load object: ";
		message += SDL_GetError();
		throw SDLError(message);
	}
}

void GameObject::render(SDL_Renderer *renderer)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &position);
	SDL_DestroyTexture(texture);
}

GameObject::~GameObject()
{
	SDL_FreeSurface(surface);
	surface = nullptr;
}
