#include "MenuButton.h"

MenuButton::MenuButton(const char * const inText, SDL_Rect & inPosition, TTF_Font* inFont, SceneName inTargetScene) :
text(inText), position(inPosition), font(inFont), targetScene(inTargetScene)
{
	color = white;
	buttonState = ButtonState::NOTHING;
}

void MenuButton::render(SDL_Renderer* renderer)
{
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
	position.w = surface->w;
	position.h = surface->h;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &position);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void MenuButton::handleEvent(SDL_Event& event)
{
	if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x < position.x || x > position.x + position.w || y < position.y || y > position.y + position.h)
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

void MenuButton::update(SceneManager &sceneManager)
{
	if (buttonState == ButtonState::RELEASED)
		sceneManager.switchScene(targetScene);
}