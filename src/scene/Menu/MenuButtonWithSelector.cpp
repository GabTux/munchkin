#include "MenuButtonWithSelector.h"

MenuButtonWithSelector::MenuButtonWithSelector(const char *const inText, SceneManager& inSceneManager, SDL_Rect &buttonPosition, TTF_Font *inFont,
																							 SceneName inTargetScene, const char *const fileNameSelector, SDL_Rect &selPosition) :
MenuButton(inText, inSceneManager, buttonPosition, inFont, inTargetScene), MenuSelector(fileNameSelector, selPosition)
{
}

void MenuButtonWithSelector::update()
{
	showSelector = (buttonState == ButtonState::ACTIVE);
}

void MenuButtonWithSelector::render(SDL_Renderer* renderer)
{
	MenuButton::render(renderer);
	MenuSelector::render(renderer);
}

void MenuButtonWithSelector::setDefault()
{
	MenuButton::setDefault();
	MenuSelector::setDefault();
}
