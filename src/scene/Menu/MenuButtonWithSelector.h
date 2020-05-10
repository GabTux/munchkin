#pragma once

#include "MenuSelector.h"
#include "MenuButton.h"

/**
 * Wrapper that merges selector and menu button.
 */
class MenuButtonWithSelector : public MenuButton, public MenuSelector
{
	public:
		/**
		 * Construct button and selector.
		 * @param inText Text on button.
		 * @param inSceneManager Reference to scene manager.
		 * @param buttonPosition Position of button.
		 * @param inFont Font on button.
		 * @param inTargetScene Target scene, when button is clicked.
		 * @param fileNameSelector Path to bmp selector image.
		 * @param selPosition Position of selector.
		 */
		MenuButtonWithSelector(const char * const inText, SceneManager& inSceneManager, SDL_Rect & buttonPosition, TTF_Font* inFont, SceneName inTargetScene,
													 const char * const fileNameSelector, SDL_Rect& selPosition);

		/**
		 * Render button and selector.
		 * @param renderer Reference to desired renderer.
		 */
		void render(SDL_Renderer* renderer) override;

		/**
		 * If button is active, show selector.
		 */
		void update();
};
