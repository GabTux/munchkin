#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "../Exceptions.h"

/**
 * Class for managing background.
 */
class Background
{
	private:
		SDL_Surface* surfaceBackground;

	public:
		/**
		 * Construct new background.
		 * @param wallpaperPath path to wallpaper.
		 */
		explicit Background(const char * const wallpaperPath);

		/**
		 * Clear used resources.
		 */
		~Background();

		/**
		 * Update graphic resources.
		 */
		void update();

		/**
		 * Render background.
		 */
		void render(SDL_Renderer*);
};