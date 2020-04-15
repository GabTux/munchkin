#pragma once

#include <SDL2/SDL.h>
#include "../SceneManager.h"


class MenuItem
{
	public:
		virtual void render(SDL_Renderer* renderer) {};
		virtual void handleEvent(SDL_Event& event) {};
		virtual void update(SceneManager& sceneManager) {};
};