#include "Card.h"

Card::Card(SDL_Rect & pos) : position(pos)
{

}

void Card::render(SDL_Renderer *renderer)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, cardSurface);
	SDL_RenderCopy(renderer, texture, NULL, &position);
	SDL_DestroyTexture(texture);
}