#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../constants.h"
#include "../SceneManager.h"
#include "MenuItem.h"

enum class ButtonState
{
	NOTHING,
	ACTIVE,
	PRESSED,
	RELEASED,
};

class MenuButton : public MenuItem
{
	private:
		const char * const text;
		SDL_Rect position;
		TTF_Font* font;
		SDL_Color white = {255, 255, 255};
		SceneName targetScene;

	public:
		MenuButton(const char * const inText, SDL_Rect & inPosition, TTF_Font *inFont, SceneName inTargetScene);
		void render(SDL_Renderer* renderer) override;
		void handleEvent(SDL_Event& event) override;
		void update(SceneManager& sceneManager) override;

		ButtonState buttonState;
		SDL_Color color;
};