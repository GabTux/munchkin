#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../constants.h"
#include "../SceneManager.h"
#include "../../Exceptions.h"

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
		SDL_Color white = {255, 255, 255 };
		SDL_Color red = { 188, 26, 26 };
		SDL_Color blue = {41, 57, 201 };
		SDL_Color color;
		SceneManager& sceneManager;
		SceneName targetScene;
		SDL_Rect buttonPosition;

	protected:
		/**
		 * Actual position of button.
		 * It is used in wrapper around button and selector, to determine, if button is active.
		 */
		ButtonState buttonState;

	public:
		/**
		 * Constructs new button.
		 * @param inText Text of new button.
		 * @param inSceneManager Reference to scene manager.
		 * @param inPosition Position where will be button placed.
		 * @param inFont Font which will be used.
		 * @param inTargetScene Target scene to that will be switched, when button is released.
		 */
		MenuButton(const char * const inText, SceneManager& inSceneManager, SDL_Rect& inPosition, TTF_Font* inFont, SceneName inTargetScene);

		/**
		 * Render button.
		 * @param renderer Reference to renderer, where will be button rendered.
		 */
		virtual void render(SDL_Renderer* renderer);

		 /**
		 * Handle caught event.
	   * Typically it switches buttonState according to event.
		 * @param event Reference to caught event.
		 */
		virtual void handleEvent(SDL_Event& event);
};