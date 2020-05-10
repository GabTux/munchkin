#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "../Exceptions.h"
#include "GraphicObject.h"
#include "../constants.h"

/**
 * Class that represents movable game object.
 */
class GameObject : public GraphicObject
{
	private:
		int moveX;
		int moveY;
		SDL_Surface* surface;

	protected:
		/**
		 * Position of graphic object.
		 */
		SDL_Rect position;

	public:
		/**
		 * Construct new object.
		 * @param fileName Path to bmp image.
		 * @param inPosition Starting position.
		 * @param inMoveX How fast move on X.
		 * @param inMoveY How fast move on Y.
		 */
		GameObject(const char * const fileName, SDL_Rect & inPosition, int inMoveX = 0, int inMoveY = 0);

		/**
		 * Handle user input.
		 * @param event Reference to caught event.
		 */
		void handleEvent(SDL_Event & event) override { };

		/**
		 * Update parameters, according to events.
		 */
		void update() override { }

		/**
		 * Render object.
		 * @param renderer Reference to renderer.
		 */
		void render(SDL_Renderer* renderer) override;

		/**
		 * Move object.
		 */
		virtual void move();

		/**
		 * Move object to different place.
		 * @param inPos Where to move.
		 */
		virtual void setPosition(SDL_Rect& inPos);

		/**
		 * Get object position.
		 * @return Position.
		 */
		[[nodiscard]] SDL_Rect getPosition() override { return position; };

		/**
		 * Clear used resources.
		 */
		virtual ~GameObject();
};

