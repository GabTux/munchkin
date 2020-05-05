#pragma once

#include <SDL2/SDL.h>

#include "../GameObject.h"

/**
 * Class card.
 */
class Card : public GameObject
{
	private:
		SDL_Rect position;
		SDL_Surface* cardSurface;

	public:
		/**
		 * Construct new card.
		 * @param pos Position, where card should be rendered.
		 */
		Card(SDL_Rect & pos);

		/**
		 * Render card.
		 * @param renderer Reference to renderer.
		 */
		void render(SDL_Renderer* renderer) override;
};
