#include "GameObject.h"

GameObject::GameObject(const char * const fileName, SDL_Rect & inPosition, int inMoveX, int inMoveY) :
moveX(inMoveX), moveY(inMoveY), surface(SDL_LoadBMP(fileName)), position(inPosition)
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

void GameObject::move()
{
	if (position.y <= 0 || position.y + position.h > constants::windowHeight)
		moveY = -moveY;
	if (position.x <= 0 || position.x + position.w > constants::windowWidth)
		moveX = -moveX;

	position.y += moveY;
	position.x += moveX;
}

void GameObject::setPosition(SDL_Rect &inPos)
{
	position = inPos;
}
