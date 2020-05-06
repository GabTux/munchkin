#pragma once

#include <SDL2/SDL.h>
/**
 * Object that indicates selected button.
 */
class MenuSelector
{
	private:
		SDL_Rect selectorPosition;
		SDL_Surface* selectorSurface;

public:
		/**
		 * Construct new selector.
		 * @param fileName Path to bmp image.
		 * @param inPosition Position, where it will be placed.
		 */
		MenuSelector(const char * const fileName, SDL_Rect & inPosition);

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
