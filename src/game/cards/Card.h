#pragma once

#include <SDL2/SDL.h>

#include "../GameObject.h"
#include "../GameButton.h"

/**
 * Class card.
 */
class Card : public GameObject
{
	private:
		std::string helpText;
		std::unique_ptr<GameButton> playButton;
		std::unique_ptr<GameButton> helpButton;
		bool buttonsEnabled;

	public:
		/**
		 * Construct new card.
		 * @param fileName Path to bmp image.
		 * @param inPos Starting position.
		 * @param inHelpText Help text, that will be shown, if button triggered.
		 */
		Card(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText);

		/**
		 * React to caught events.
		 * Handle events for buttons and for card.
		 * @param event Caught event.
		 */
		void handleEvent(SDL_Event& event) override;

		/**
		 * Update according to user input.
		 * If help button is pressed, show help.
		 * TODO: If play button pressed -> play.
		 */
		void update() override;

		/**
		 * Render card.
		 * @param renderer Where to render.
		 */
		void render(SDL_Renderer* renderer) override;

		/**
		 * Move card to different position.
		 * @param inPos Where to move.
		 */
		void setPosition(SDL_Rect& inPos) override;

		/**
		 * @return For each type, return specific value.
		 */
		[[nodiscard]] virtual int getValue() const = 0;
};
