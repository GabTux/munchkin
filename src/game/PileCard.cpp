#include "PileCard.h"
#include "Player.h"

PileCard::PileCard(std::string inTextPacked, std::string inTextUnpacked, std::vector<std::shared_ptr<Card>> &inCards,
				SDL_Rect& inButtonPos, SDL_Rect& inPilePos, TTF_Font* menuFont,  std::shared_ptr<CardDeck>& inDoorDeckGarbage, std::shared_ptr<CardDeck>& inTreasureDeckGarbage) :
textPacked(std::move(inTextPacked)), textUnpacked(std::move(inTextUnpacked)), buttonPos(inButtonPos),
pilePos(inPilePos), doorDeckGarbage(inDoorDeckGarbage), treasureDeckGarbage(inTreasureDeckGarbage), cards(inCards)
{
	switchButton = std::make_unique<GameButton>(textPacked+" "+std::to_string(value), inButtonPos, menuFont);

	SDL_Rect leftPos = {pilePos.x - 50, pilePos.y+constants::cardHeight/3, 0, 0};
	SDL_Rect rightPos = {pilePos.x + 3 * (constants::cardWidth + (int)showCards) + 10, pilePos.y+constants::cardHeight/3, 0, 0};
	std::string leftText = "<"; std::string rightText = ">";
	arrowLeft = std::make_unique<GameButton>(leftText, leftPos, menuFont);
	arrowRight = std::make_unique<GameButton>(rightText, rightPos, menuFont);

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
	checkForPlayedCards();
	if (pileState == PileState::UNPACKED)
		updateUnpacked();
}

void PileCard::render(SDL_Renderer *renderer)
{
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
	{
		cards[i]->update();
	}
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
	std::vector<std::shared_ptr<Card>> tmpVect;
	cards = tmpVect;
	updateValue();
	switchButton->setText(textPacked+" "+std::to_string(value));
	switchButton->setDefault();
	pileState = PileState::PACKED;
	arrowLeft->setDefault();
	arrowRight->setDefault();
	renderIndex = 0;
}

void PileCard::addCard(const std::shared_ptr<Card>& inCard)
{
	cards.push_back(inCard);
	updateValue();
	if (pileState == PileState::PACKED)
		switchButton->setText(textPacked+" "+std::to_string(value));
}

void PileCard::pack()
{
	updateValue();
	switchButton->setText(textPacked+" "+std::to_string(value));
	pileState = PileState::PACKED;
}

std::shared_ptr<Card> PileCard::getRandomCard()
{
	int randPos = randomInt(0, (int)cards.size()-1);
	std::shared_ptr<Card> res = cards[randPos];
	cards.erase(cards.begin()+randPos);

	updateValue();
	if (pileState == PileState::PACKED)
		switchButton->setText(textPacked+" "+std::to_string(value));
	if (pileState == PileState::UNPACKED && renderIndex)
		renderIndex--;

	return res;
}

void PileCard::update(std::shared_ptr<Card>& inActCard, GameState inActState)
{
	actCard = inActCard;
	actState = inActState;
	update();
}

int PileCard::cantPlayDialog(std::string& inMessage)
{
	const SDL_MessageBoxButtonData buttons[] = {
					{ /* .flags, .buttonid, .text */        0, 0, "THROW AWAY" },
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "BACK" }
	};
	const SDL_MessageBoxColorScheme colorScheme = {
					{
									{ 186, 112, 0 },
									{   255, 255, 255 },
									{ 255, 255, 0 },
									{   41, 57, 201 },
									{ 255, 0, 255 }
					}
	};
	const SDL_MessageBoxData messageboxdata = {SDL_MESSAGEBOX_INFORMATION,nullptr,"Can't play",
	                                           inMessage.c_str(),SDL_arraysize(buttons), buttons, &colorScheme };
	int buttonID;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonID) < 0)
	{
		std::string message = "Unable to pop up message box"; message += SDL_GetError();
		throw SDLError(message);
	}

	return buttonID;
}

void PileCard::handlePlayedCard(unsigned int cardInx)
{
	std::string retMessage;
	bool resPlay;
	auto opponentTmp = opponent.lock();
	auto ownerTmp = owner.lock();
	if (cards[cardInx]->isCurse())
		resPlay = cards[cardInx]->play(opponentTmp, actCard, actState, retMessage);
	else
		resPlay = cards[cardInx]->play(ownerTmp, actCard, actState, retMessage);
	if (!resPlay)
	{
		if (cantPlayDialog(retMessage) == 0)
		{
			cards[cardInx]->throwAway();
			cards[cardInx]->setDefault();
			if (cards[cardInx]->isTreasure())
				treasureDeckGarbage->addCard(cards[cardInx]);
			else
				doorDeckGarbage->addCard(cards[cardInx]);
			cards.erase(cards.begin() + cardInx);
			updateValue();
			ownerTmp->updateIndicators();
			if (renderIndex > 0) renderIndex--;
		}
		else
			cards[cardInx]->setDefault();
	}
	else
	{
		if (cards[cardInx]->getState() != CardState::MOVED)
		{
			cards[cardInx]->setDefault();
			if (cards[cardInx]->isTreasure())
				treasureDeckGarbage->addCard(cards[cardInx]);
			else
				doorDeckGarbage->addCard(cards[cardInx]);
			cards.erase(cards.begin() + cardInx);
			updateValue();
			if (renderIndex > 0) renderIndex--;
		}
	}
}

int PileCard::getValue()
{
	updateValue();
	return value;
}

void PileCard::setPlayers(std::shared_ptr<Player> inOwner, std::shared_ptr<Player> inOpponent)
{
	owner = inOwner;
	opponent = inOpponent;
}

void PileCard::unpack()
{
	switchButton->setText(textUnpacked);
	pileState = PileState::UNPACKED;
}

void PileCard::checkForPlayedCards()
{
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		if (cards[i]->getState() == CardState::PLAYED)
		{
			handlePlayedCard(i);
		}
		if (cards[i]->getState() == CardState::MOVED)
		{
			auto ownerTmp = owner.lock();
			ownerTmp->toInvCard(cards[i]);
			cards.erase(cards.begin() + i);
			updateValue();
			if (renderIndex) renderIndex--;
		}
	}
}

void PileCard::updateIndicator()
{
	updateValue();
	if (pileState == PileState::PACKED)
		switchButton->setText(textPacked+" "+std::to_string(value));
}

std::ostream& operator<<(std::ostream &os, const PileCard& inPileCard)
{
	std::string res;
	std::size_t checkHash;
	for (auto& it: inPileCard.cards)
	{
		res += it->isTreasure() ? 't' : 'd';
		res += " " + std::to_string(it->getID()) + " ";
	}
	res += "d -1";

	checkSum(res, checkHash);
	encryptDecrypt(res);

	os << res << std::endl << checkHash;
	return os;
}
