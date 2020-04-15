#pragma once

#include <SDL2/SDL.h>

class GameObject
{
	public:
		virtual void handle_event(SDL_Event & event) {};
		virtual void update() {};
		virtual void render(SDL_Renderer* renderer) {};
};

