#pragma once

#include <SDL2/SDL.h>

#include "../GameObject.h"

/**
 * Class card.
 */
class Card : public GameObject
{
	private:

	public:
		/**
		 * Construct new card.
		 * @param pos Position, where card should be rendered.
		 */
		Card(const char * const fileName, SDL_Rect & pos);
};
