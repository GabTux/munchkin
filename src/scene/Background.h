#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>
#include "../Exceptions.h"
#include "../game/GraphicObject.h"

/**
 * Class for managing background.
 */
class Background : public GraphicObject
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

		void handleEvent(SDL_Event& event) override { }

		/**
		 * Update graphic resources.
		 */
		void update() override;

		/**
		 * Render background.
		 */
		void render(SDL_Renderer*) override;
};