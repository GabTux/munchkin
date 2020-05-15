#pragma once

#include <SDL2/SDL.h>

/**
 * Base class for many Graphics Objects.
 */
class GraphicObject
{
	public:
		/**
		 * React to user input.
		 * @param event Caught event.
		 */
		virtual void handleEvent(SDL_Event& event) = 0;

		/**
		 * Update according to input.
		 */
		virtual void update() = 0;

		/**
		 * Render object.
		 * @param renderer Where to render.
		 */
		virtual void render(SDL_Renderer* renderer) = 0;

		/**
		 * Get position of object.
		 * @return Position.
		 */
		[[nodiscard]] virtual SDL_Rect getPosition() = 0;

		virtual void setDefault() { }
};