#pragma once

#include <SDL2/SDL.h>

#include "MenuItem.h"

class MenuSelector : public MenuItem
{
	private:
		SDL_Rect position;
		SDL_Surface* surface;

public:
		MenuSelector(const char * const, SDL_Rect & inPosition);
		void render(SDL_Renderer* renderer) override;
		~MenuSelector();

		bool show;
};
