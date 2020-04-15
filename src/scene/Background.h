#pragma once

#include <SDL2/SDL.h>

class Background
{
	private:
		SDL_Surface* surfaceBackground;

	public:
		explicit Background(const char * const);
		~Background();
		void update();
		void render(SDL_Renderer*);
};