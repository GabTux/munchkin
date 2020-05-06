#include "MenuButtonWithSelector.h"

MenuButtonWithSelector::MenuButtonWithSelector(const char *const inText, SDL_Rect &buttonPosition, TTF_Font *inFont,
																							 SceneName inTargetScene, const char *const fileNameSelector, SDL_Rect &selPosition) :
MenuButton(inText, buttonPosition, inFont, inTargetScene), MenuSelector(fileNameSelector, selPosition)
{
}

void MenuButtonWithSelector::render(SDL_Renderer* renderer)
{
	MenuButton::render(renderer);
	MenuSelector::render(renderer);
}
