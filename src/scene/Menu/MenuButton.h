#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../constants.h"
#include "../SceneManager.h"

enum class ButtonState
{
	NOTHING,
	ACTIVE,
	PRESSED,
	RELEASED,
};

class MenuButton
{
	private:
		const char * const text;
		SDL_Rect position;
		TTF_Font* font;
		SDL_Color white = {255, 255, 255};

	public:
		/**
		 * Constructs new button.
		 * @param inText Text of new button.
		 * @param inPosition Position where will be button placed.
		 * @param inFont Font which will be used.
		 * @param inTargetScene Target scene to that will be switched, when button is released.
		 */
		MenuButton(const char * const inText, SDL_Rect & inPosition, TTF_Font *inFont, SceneName inTargetScene);

		/**
		 * Render button.
		 * @param renderer Reference to renderer, where will be button rendered.
		 */
		void render(SDL_Renderer* renderer);

		/**
		 * Handle catched event.
		 * @param event Reference to catched event.
		 */
		void handleEvent(SDL_Event& event);

		/**
		 * Actual button state.
		 */
		ButtonState buttonState;

		/**
		 * Actual text color.
		 */
		SDL_Color color;

		/**
		 * Target scene, which will be used, when button is released.
		 */
		SceneName targetScene;
};