#pragma once

#include <SDL2/SDL.h>

class GameObject
{
	public:
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
		virtual void render(SDL_Renderer* renderer) { }
};

