#pragma once

#include "../scene/Menu/MenuButton.h"
#include "GraphicObject.h"
#include "../Exceptions.h"

/**
 * Class for buttons in Game.
 */
class GameButton : public GraphicObject
{
	private:
		SDL_Color white = {255, 255, 255 };
		SDL_Color red = { 188, 26, 26 };
		SDL_Color blue = {41, 57, 201 };
		SDL_Color color;
		ButtonState buttonState;
		std::string text;
		TTF_Font* font;
		SDL_Rect position;

	public:
		/**
		 * Construct new button.
		 * @param inText Text on button.
		 * @param inPosition Position of button.
		 * @param inFont Font used.
		 */
		GameButton(std::string inText, SDL_Rect& inPosition, TTF_Font* inFont);

		/**
		 * Set state according to user input.
		 * @param event Caught event.
		 */
		void handleEvent(SDL_Event& event) override;

		/**
		 * Do nothing.
		 */
		void update() override { }

		/**
		 * Render button.
		 * @param renderer Where to render.
		 */
		void render(SDL_Renderer* renderer) override;

		/**
		 * Set button to start state.
		 */
		void setDefault() override;

		/**
		 * Change text on button.
		 * @param inText New text.
		 */
		void setText(std::string inText);

		/**
		 * Get button actual state.
		 * @return Button State.
		 */
		[[nodiscard]] ButtonState getState() { return buttonState; };

		/**
		 * Move button to different place.
		 * @param inPos Where to move.
		 */
		void setPosition(SDL_Rect& inPos);

		/**
		 * Get actual position of button.
		 * @return Position.
		 */
		[[nodiscard]] SDL_Rect getPosition() override { return position; };
};