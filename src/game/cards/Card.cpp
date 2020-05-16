#include "Card.h"

Card::Card(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText) :
GameObject(fileName, inPos), helpText(inHelpText)
{
	TTF_Font* font = TTF_OpenFont(constants::genericFontPath, constants::cardButtonSize);
	playButton = std::make_unique<GameButton>("Play", position, font);
	helpButton = std::make_unique<GameButton>("Help", position, font);
}

void Card::handleEvent(SDL_Event &event)
{
	if (buttonsEnabled)
	{
		playButton->handleEvent(event);
		helpButton->handleEvent(event);
	}
	GameObject::handleEvent(event);
}

void Card::update()
{
	if (buttonsEnabled)
	{
		if (helpButton->getState() == ButtonState::RELEASED)
		{
			showHelp();
		}
	}
	GameObject::update();
}

void Card::render(SDL_Renderer *renderer)
{
	if (buttonsEnabled)
	{
		playButton->render(renderer);
		helpButton->render(renderer);
	}
	GameObject::render(renderer);
}

void Card::setPosition(SDL_Rect &inPos)
{
	GameObject::setPosition(inPos);
	SDL_Rect playPos = {position.x+20, position.y+position.h+5, 0, 0};
	playButton->setPosition(playPos);
	SDL_Rect helpPos = {playButton->getPosition().x+playButton->getPosition().w+40, position.y+position.h+5, 0, 0};
	helpButton->setPosition(helpPos);
}

void Card::showHelp()
{
	if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Help",helpText.c_str(), NULL) != 0)
	{
		std::string message = "Unable to pop up message box: "; message += SDL_GetError();
		throw SDLError(message);
	}
	helpButton->setDefault();
}
