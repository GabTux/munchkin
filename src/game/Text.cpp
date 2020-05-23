#include "Text.h"

Text::Text(std::string inText, SDL_Rect inPos, TTF_Font* inFont, SDL_Color inColor, SDL_Renderer* inRenderer) :
showText(std::move(inText)), position(inPos), font(inFont), color(inColor), mainRenderer(inRenderer)
{
	SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, showText.c_str(), color, 1000);
	if (!surface)
	{
		std::string message = "Unable to create new text: "; message += TTF_GetError();
		throw TTFError(message);
	}
	position.w = surface->w;
	position.h = surface->h;
	textTexture = SDL_CreateTextureFromSurface(mainRenderer, surface);
	SDL_FreeSurface(surface);
}

void Text::render(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, textTexture, nullptr, &position);
}

void Text::setText(std::string inText)
{
	showText = std::move(inText);
	SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, showText.c_str(), color, 1000);
	if (!surface)
	{
		std::string message = "Unable to create new text: "; message += TTF_GetError();
		throw TTFError(message);
	}
	position.w = surface->w;
	position.h = surface->h;
	textTexture = SDL_CreateTextureFromSurface(mainRenderer, surface);
	SDL_FreeSurface(surface);
}

Text::~Text()
{
	SDL_DestroyTexture(textTexture);
}
