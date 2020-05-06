#include "MenuButton.h"

MenuButton::MenuButton(const char * const inText, SDL_Rect & inPosition, TTF_Font* inFont, SceneName inTargetScene) :
text(inText), font(inFont), buttonPosition(inPosition), buttonState(ButtonState::NOTHING), color(SDL_Color{255, 255, 255}), targetScene(inTargetScene)
{
}

void MenuButton::render(SDL_Renderer* renderer)
{
	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
	buttonPosition.w = surface->w;
	buttonPosition.h = surface->h;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &buttonPosition);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void MenuButton::handleEvent(SDL_Event& event)
{
	if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x < buttonPosition.x || x > buttonPosition.x + buttonPosition.w || y < buttonPosition.y || y > buttonPosition.y + buttonPosition.h)
			buttonState = ButtonState::NOTHING;
		else
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
					buttonState = ButtonState::ACTIVE;
					break;

				case SDL_MOUSEBUTTONDOWN:
					buttonState = ButtonState::PRESSED;
					break;

				case SDL_MOUSEBUTTONUP:
					buttonState = ButtonState::RELEASED;
					break;
			}
	}
}