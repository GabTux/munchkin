#pragma once

#include <SDL2/SDL.h>
#include "../../game/GraphicObject.h"

/**
 * Object that indicates selected button.
 */
class MenuSelector : virtual public GraphicObject
{
	private:
		SDL_Rect selectorPosition;
		SDL_Surface* selectorSurface;

	protected:
		/**
		 * Decides if selector should be visible.
		 * Used in wrapper that connects selector and button.
		 */
		bool showSelector;

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
		void render(SDL_Renderer* renderer) override;

		/**
		 * Clear object.
		 */
		~MenuSelector();

		/**
		 * Reset object to default state.
		 */
		void setDefault() override;
};
