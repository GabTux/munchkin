#include "GameButton.h"

#include <utility>

GameButton::GameButton(std::string inText, SDL_Rect &inPosition, TTF_Font* inFont) :
color(SDL_Color{255, 255, 255}), text(std::move(inText)), font(inFont), position(inPosition)
{
	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	if (!surface)
	{
		std::string message = "Unable to create surface: "; message += TTF_GetError();
		throw TTFError(message);
	}
	position.w = surface->w;
	position.h = surface->h;
}

void GameButton::render(SDL_Renderer* renderer)
{
	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	if (!surface)
	{
		std::string message = "Unable to create surface: "; message += TTF_GetError();
		throw TTFError(message);
	}
	position.w = surface->w;
	position.h = surface->h;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		std::string message = "Unable to create texture: "; message += SDL_GetError();
		throw SDLError(message);
	}
	SDL_RenderCopy(renderer, texture, NULL, &position);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void GameButton::handleEvent(SDL_Event &event)
{
	if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x < position.x || x > position.x + position.w || y < position.y || y > position.y + position.h)
		{
			buttonState = ButtonState::NOTHING;
			color = white;
		}
		else
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
					buttonState = ButtonState::ACTIVE;
					color = red;
					break;

				case SDL_MOUSEBUTTONDOWN:
					buttonState = ButtonState::PRESSED;
					color = blue;
					break;

				case SDL_MOUSEBUTTONUP:
					buttonState = ButtonState::RELEASED;
					break;
			}
	}
}

void GameButton::setDefault()
{
	color = white;
	buttonState = ButtonState::NOTHING;
}

void GameButton::setText(std::string inText)
{
	text = inText;
}

void GameButton::setPosition(SDL_Rect& inPos)
{
	position.x = inPos.x;
	position.y = inPos.y;
}
