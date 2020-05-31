#include "Card.h"

int Card::cardCounter = 0;

Card::Card(const char * const fileName, SDL_Rect & inPos, std::string& inHelpText, TTF_Font* inFont) :
GameObject(fileName, inPos), helpText(inHelpText)
{
	id = cardCounter++;
	playButton = std::make_unique<GameButton>("Play", position, inFont);
	helpButton = std::make_unique<GameButton>("Help", position, inFont);
}

void Card::handleEvent(SDL_Event &event)
{
	if (playEnabled) playButton->handleEvent(event);
	if (helpEnabled) helpButton->handleEvent(event);
	GameObject::handleEvent(event);
}

void Card::update()
{
	if (helpEnabled && helpButton->getState() == ButtonState::RELEASED)
		showHelp();
	else if (playEnabled && playButton->getState() == ButtonState::RELEASED)
	{
		cardState = CardState::PLAYED;
		playButton->setDefault();
	}
	GameObject::update();
}

void Card::render(SDL_Renderer *renderer)
{
	if (playEnabled) playButton->render(renderer);
	if (helpEnabled) helpButton->render(renderer);
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

void Card::setDefault()
{
	cardState = CardState::NOTHING;
	changeButtons(true, true);
	GraphicObject::setDefault();
}

void Card::changeButtons(bool enablePlay, bool enableHelp)
{
	playEnabled = enablePlay;
	helpEnabled = enableHelp;
}
