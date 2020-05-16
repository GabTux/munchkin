#include "PileCard.h"

PileCard::PileCard(std::string inTextPacked, std::string inTextUnpacked, std::vector<std::shared_ptr<Card>> &inCards,
				SDL_Rect& inButtonPos, SDL_Rect& inPilePos) :
textPacked(std::move(inTextPacked)), textUnpacked(std::move(inTextUnpacked)), buttonPos(inButtonPos),
pilePos(inPilePos), cards(inCards)
{
	TTF_Font* font = TTF_OpenFont(constants::genericFontPath, constants::menuButtonTextSize);
	if (!font)
	{
		std::string message = "Unable to load Font: "; message += TTF_GetError();
		throw TTFError(message);
	}

	switchButton = std::make_unique<GameButton>(textPacked, inButtonPos, font);

	SDL_Rect leftPos = {pilePos.x - 50, pilePos.y+constants::cardHeight/3, 0, 0};
	SDL_Rect rightPos = {pilePos.x + 3 * (constants::cardWidth + (int)showCards) + 10, pilePos.y+constants::cardHeight/3, 0, 0};
	std::string leftText = "<"; std::string rightText = ">";
	arrowLeft = std::make_unique<GameButton>(leftText, leftPos, font);
	arrowRight = std::make_unique<GameButton>(rightText, rightPos, font);

	// prepare cards
	renderIndex = 0;
}

void PileCard::handleEvent(SDL_Event &event)
{
	switchButton->handleEvent(event);
	if (pileState == PileState::UNPACKED)
		handleEventUnpacked(event);
}

void PileCard::update()
{
	if (switchButton->getState() == ButtonState::RELEASED)
	{
		if (pileState == PileState::UNPACKED)
		{
			pileState = PileState::PACKED;
			renderIndex = 0;
			updateValue();
			switchButton->setText(textPacked+" "+std::to_string(value));
		}
		else
		{
			pileState = PileState::UNPACKED;
			switchButton->setText(textUnpacked);
		}
		switchButton->setDefault();
	}
	if (pileState == PileState::UNPACKED)
		updateUnpacked();
}

void PileCard::render(SDL_Renderer *renderer)
{
	if (firstRun)
	{
		switchButton->setText(textPacked+" "+std::to_string(value));
		firstRun = false;
	}
	switchButton->render(renderer);
	if (pileState == PileState::UNPACKED)
		renderUnpacked(renderer);
}

void PileCard::renderUnpacked(SDL_Renderer *renderer)
{
	if (cards.empty())
		return;

	if (renderIndex > 0) arrowLeft->render(renderer);
	if (cards.size() > renderIndex + showCards) arrowRight->render(renderer);

	SDL_Rect newCardPos = {pilePos.x, pilePos.y, 0, 0 };

	cards[renderIndex]->setPosition(newCardPos);
	cards[renderIndex]->render(renderer);
	for (unsigned int i = renderIndex+1; i-renderIndex < showCards && i < cards.size(); i++)
	{
		newCardPos.x = pilePos.x + (i-renderIndex) * constants::cardWidth + (i-renderIndex) * showCards;
		cards[i]->setPosition(newCardPos);
		cards[i]->render(renderer);
	}
}

void PileCard::handleEventUnpacked(SDL_Event& event)
{
	if (cards.empty())
		return;

	if (renderIndex > 0) arrowLeft->handleEvent(event);
	if (cards.size() > renderIndex + showCards) arrowRight->handleEvent(event);

	for (unsigned int i = renderIndex; i-renderIndex < showCards && i < cards.size(); i++)
		cards[i]->handleEvent(event);
}

void PileCard::updateUnpacked()
{
	if (arrowRight->getState() == ButtonState::RELEASED)
	{
		renderIndex++;
		arrowRight->setDefault();
	}
	if (arrowLeft->getState() == ButtonState::RELEASED)
	{
		renderIndex--;
		arrowLeft->setDefault();
	}

	for (unsigned int i = renderIndex; i-renderIndex < showCards && i < cards.size(); i++)
		cards[i]->update();
}

void PileCard::setCards(std::vector<std::shared_ptr<Card>>& inHandCards)
{
	cards = inHandCards;
	updateValue();
	if (pileState == PileState::PACKED)
		switchButton->setText(textPacked+" "+std::to_string(value));
}

void PileCard::setDefault()
{
	updateValue();
	switchButton->setText(textPacked+" "+std::to_string(value));
	switchButton->setDefault();
	pileState = PileState::PACKED;
	arrowLeft->setDefault();
	arrowRight->setDefault();
	renderIndex = 0;
}

void PileCard::addCard(std::shared_ptr<Card> inCard)
{
	cards.push_back(inCard);
	updateValue();
	if (pileState == PileState::PACKED)
		switchButton->setText(textPacked+" "+std::to_string(value));
}
