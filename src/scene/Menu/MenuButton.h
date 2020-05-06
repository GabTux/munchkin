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
		TTF_Font* font;

	protected:
		SDL_Rect buttonPosition;

	public:
		/**
		 * Constructs new button.
		 * @param inText Text of new button.
		 * @param inPosition Position where will be button placed.
		 * @param inFont Font which will be used.
		 * @param inTargetScene Target scene to that will be switched, when button is released.
		 */
		MenuButton(const char * const inText, SDL_Rect& inPosition, TTF_Font* inFont, SceneName inTargetScene);

		/**
		 * Render button.
		 * @param renderer Reference to renderer, where will be button rendered.
		 */
		virtual void render(SDL_Renderer* renderer);

		 /**
		 * Handle catched event.
		 * @param event Reference to catched event.
		 */
		virtual void handleEvent(SDL_Event& event);

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