#pragma once

#include <SDL2/SDL.h>
/**
 * Object that indicates selected button.
 */
class MenuSelector
{
	private:
		SDL_Rect position;
		SDL_Surface* surface;

public:
		/**
		 * Construct new selector.
		 * @param inPosition Position, where it will be placed.
		 */
		MenuSelector(const char * const, SDL_Rect & inPosition);

		/**
		 * Render selector.
		 * @param renderer Where to render.
		 */
		void render(SDL_Renderer* renderer);

		/**
		 * Clear object.
		 */
		~MenuSelector();

		/**
		 * It indicates, if selector should be visible.
		 */
		bool show;
};
