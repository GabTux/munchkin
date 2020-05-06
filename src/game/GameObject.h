#pragma once

#include <SDL2/SDL.h>

class GameObject
{
	protected:
		SDL_Surface* surface;

	public:

		GameObject(const char * const fileName, SDL_Rect & inPosition, int inMoveX = 0, int inMoveY = 0);

		/**
		 * Handle user input.
		 * @param event Reference to catched event.
		 */
		virtual void handle_event(SDL_Event & event) { }

		/**
		 * Update parameters, according to events.
		 */
		virtual void update() { }

		/**
		 * Render object.
		 * @param renderer Reference to renderer.
		 */
		virtual void render(SDL_Renderer* renderer);


		~GameObject();
		/**
		 * Where to render.
		 */
		SDL_Rect position;

		/**
		 * How fast move.
		 */
		 int moveX;
		 int moveY;
};

