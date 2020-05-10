#include "MenuButton.h"

MenuButton::MenuButton(const char * const inText, SceneManager& inSceneManager,  SDL_Rect & inPosition, TTF_Font* inFont, SceneName inTargetScene) :
text(inText), font(inFont),color(SDL_Color{255, 255, 255}),  sceneManager(inSceneManager),targetScene(inTargetScene),
buttonPosition(inPosition), buttonState(ButtonState::NOTHING)
{
}

void MenuButton::render(SDL_Renderer* renderer)
{
	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
	if (!surface)
	{
		std::string message = "Unable to create surface: "; message += TTF_GetError();
		throw TTFError(message);
	}
	buttonPosition.w = surface->w;
	buttonPosition.h = surface->h;

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		std::string message = "Unable to create texture: "; message += SDL_GetError();
		throw SDLError(message);
	}
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
					sceneManager.switchScene(targetScene);
					return;
			}
	}
}