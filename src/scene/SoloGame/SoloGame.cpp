#include "SoloGame.h"

#include <iostream>

SoloGame::SoloGame(SDLResources& inRes, SceneManager& inSceneManager) : res(inRes), sceneManager(inSceneManager)
{
}

void SoloGame::prepare()
{
	doorCardDeck = std::make_unique<CardDeck>();
	treasureCardDeck = std::make_unique<CardDeck>();
	readCards(constants::cardFile);
	doorCardDeckBack = std::make_unique<CardDeck>(*doorCardDeck);
	treasureCardDeckBack = std::make_unique<CardDeck>(*treasureCardDeck);
	gameBackground = std::make_unique<Background>(constants::gameWallpaperPath);
	SDL_Rect pos = {constants::playersX, constants::upPlayerY, 0, 0};

	std::vector<std::shared_ptr<Card>> randomCards;
	players.push_back(std::make_shared<Human>(randomCards, pos));
	pos.y = constants::downPlayerY;
	players.push_back(std::make_shared<Human>(randomCards, pos));
	setRandomPlayerCards();

	SDL_Rect buttonPos = {constants::pauseButtonX, constants::pauseButtonY, 0, 0};
	pauseButton = std::make_unique<GameButton>("PAUSE", buttonPos, res.menuFont);
	buttonPos.x = constants::actionButtonX;
	actionButton = std::make_unique<GameButton>(constants::actionButtonTexts[0], buttonPos, res.menuFont);
}

void SoloGame::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !stopped)
	{
		if (event.type == SDL_QUIT)
		{
			sceneManager.switchScene(SceneName::STOP);
			return;
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				int choice = pauseMenu();       //this will block current thread until messagebox resolved
				if (choice == 2)
				{
					sceneManager.switchScene(SceneName::MAIN_MENU);
					return;
				}
				if (choice == 1)
				{
					//TODO
				}
			}
		}
		players[actPlayerInx]->handleEvent(event);
		pauseButton->handleEvent(event);
		actionButton->handleEvent(event);
	}
}

void SoloGame::update()
{
	players[actPlayerInx]->update();
	if (pauseButton->getState() == ButtonState::RELEASED)
	{
		int choice = pauseMenu();
		if (choice == 2)
		{
			sceneManager.switchScene(SceneName::MAIN_MENU);
			return;
		}
		if (choice == 1)
		{
			//TODO
		}
	}

	if (actPlayCard)
	{
		handleActPlayCard();
	}

	if (actionButton->getState() == ButtonState::RELEASED)
	{
		switch (actStateInx)
		{
			case 0:
				kickDoor();
				break;
			case 1:
				//end fight
				actStateInx++;
				break;
			case 2:
				//end turn
				//some checks if player can end turn
				//pack pile if unpacked
				switchPlayer();
				actStateInx = 0;
				actionButton->setText(constants::actionButtonTexts[actStateInx]);
				break;
		}
		actionButton->setDefault();
	}
}

void SoloGame::render()
{
	gameBackground->render(res.mainRenderer);
	for (auto& it: players)
		it->render(res.mainRenderer);
	pauseButton->render(res.mainRenderer);
	actionButton->render(res.mainRenderer);
	if (actPlayCard) actPlayCard->render(res.mainRenderer);
}

void SoloGame::readHelp(std::ifstream& cardFile, std::string& helpText)
{
	char c = 0;
	helpText = "";
	cardFile.ignore();
	cardFile.ignore();

	while (c!='"')
	{
		cardFile.get(c);
		helpText += c;
	}
	helpText.pop_back();
	cardFile.ignore();
}

int SoloGame::pauseMenu()
{
	const SDL_MessageBoxButtonData buttons[] = {
					{ /* .flags, .buttonid, .text */        0, 0, "CONTINUE" },
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "SAVE" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "BACK TO MENU" },
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
	const SDL_MessageBoxData messageboxdata = {SDL_MESSAGEBOX_INFORMATION,NULL,"Pause menu",
					"Game paused.",SDL_arraysize(buttons), buttons, &colorScheme };
	int buttonID;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonID) < 0)
	{
		std::string message = "Unable to pop up message box"; message += SDL_GetError();
		throw SDLError(message);
	}

	return buttonID;
}

void SoloGame::readCards(const char * const fileName)
{
	std::ifstream cardFile;
	cardFile.open(fileName);
	if (!cardFile)
	{
		std::string message = "Unable to load cards, missing file " + std::string(fileName);
		throw FileError(message);
	}

	std::string cardPath;
	std::string cardType;
	std::string helpText;
	int cardCount;
	SDL_Rect defPos = {0, 0, constants::cardWidth, constants::cardHeight};
	while (cardFile >> cardPath >> cardCount >> cardType)
	{
		if (cardType == "race")
		{
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
			{
				std::shared_ptr<Card> tmpPtr = std::make_shared<RaceCard>(cardPath.c_str(), defPos, helpText);
				doorCardDeck->addCard(tmpPtr);
			}
		}
		else if (cardType == "curse")
		{
			int loseLevel;
			cardFile >> loseLevel;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
			{
				std::shared_ptr<Card> tmpPtr = std::make_shared<CurseCard>(cardPath.c_str(), defPos, helpText, loseLevel);
				doorCardDeck->addCard(tmpPtr);
			}
		}
		else if (cardType == "monsterBoost")
		{
			int boostNum;
			cardFile >> boostNum;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
			{
				std::shared_ptr<Card> tmpPtr = std::make_shared<MonsterBoostCard>(cardPath.c_str(), defPos, helpText, boostNum);
				doorCardDeck->addCard(tmpPtr);
			}
		}
		else if (cardType == "monster")
		{
			int monsterLevel, badStuffVal;
			std::string badStuff;
			cardFile >> monsterLevel;
			cardFile >> badStuff;
			cardFile >> badStuffVal;
			BadStuffType badStuffType = (badStuff == "level") ? BadStuffType::LEVEL : BadStuffType::CARDS;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
			{
				std::shared_ptr<Card> tmpPtr = std::make_shared<MonsterCard>(cardPath.c_str(), defPos, helpText, badStuffType,
				                                                             badStuffVal, monsterLevel);
				doorCardDeck->addCard(tmpPtr);
			}
		}
		else if (cardType == "item")
		{
			std::string itemType;
			int combatBonus;
			cardFile >> combatBonus;
			cardFile >> itemType;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
			{
				std::shared_ptr<Card> tmpPtr = std::make_shared<ItemCard>(cardPath.c_str(), defPos, helpText, combatBonus);
				treasureCardDeck->addCard(tmpPtr);
			}
		}
		else if (cardType == "oneUseItem")
		{
			int combatBonus;
			cardFile >> combatBonus;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
			{
				std::shared_ptr<Card> tmpPtr = std::make_shared<OneUseItemCard>(cardPath.c_str(), defPos, helpText,
				                                                                combatBonus);
				treasureCardDeck->addCard(tmpPtr);
			}
		}
		else if (cardType == "levelup")
		{
			int level;
			cardFile >> level;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
			{
				std::shared_ptr<Card> tmpPtr = std::make_shared<LevelUpCard>(cardPath.c_str(), defPos, helpText, level);
				doorCardDeck->addCard(tmpPtr);
			}
		}
		else if (cardType == "boost")
		{
			int boost;
			cardFile >> boost;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
			{
				std::shared_ptr<Card> tmpPtr = std::make_shared<BoostCard>(cardPath.c_str(), defPos, helpText, boost);
				doorCardDeck->addCard(tmpPtr);
			}
		}
	}
}

void SoloGame::restart()
{
	for (auto& it: players)
		it->setDefault();
	doorCardDeck = std::make_unique<CardDeck>(*doorCardDeckBack);
	treasureCardDeck = std::make_unique<CardDeck>(*treasureCardDeckBack);
	std::vector<std::shared_ptr<Card>> randomCards;

	setRandomPlayerCards();

	pauseButton->setDefault();
	actionButton->setText(constants::actionButtonTexts[0]);
	actionButton->setDefault();
	stopped = false;
	actPlayerInx = 0;
	actStateInx = 0;
	actPlayCard = nullptr;
}

void SoloGame::getRandomCards(std::unique_ptr<CardDeck>& inCards, std::vector<std::shared_ptr<Card>>& outCards, int count)
{
	for (int i = 0; i < count; i++)
		outCards.push_back(inCards->getCard());
}

void SoloGame::stopScene()
{
	stopped = true;
}

void SoloGame::kickDoor()
{
	actPlayCard = doorCardDeck->getCard();
	SDL_Rect actCardPos = {constants::actCardX, constants::actCardY, 0, 0};
	actPlayCard->setPosition(actCardPos);
	actPlayCard->changeButtons(false);
}

void SoloGame::handleActPlayCard()
{
	switch (actStateInx)
	{
		case 0:
			handleKicked();
			break;
	}
}

void SoloGame::handleKicked()
{
	actPlayCard->showHelp();
	if (actPlayCard->isMonster())
	{
		//TODO:
		//FIGHT
		actStateInx++;
		// tmp fix
		actPlayCard = nullptr;
	}
	else if (actPlayCard->isCurse())
	{
		//TODO:
		//THAT CURSE ON PLAYER
		actStateInx += 2;
		actPlayCard = nullptr;
	}
	else
	{
		actPlayCard->changeButtons(true);
		players[actPlayerInx]->gotCard(actPlayCard);
		actPlayCard = nullptr;
		actStateInx += 2;
	}
	actionButton->setText(constants::actionButtonTexts[actStateInx]);
}

void SoloGame::setRandomPlayerCards()
{
	std::vector<std::shared_ptr<Card>> randomCards;

	for (auto& it: players)
	{
		randomCards.clear();
		getRandomCards(doorCardDeck, randomCards, 4);
		getRandomCards(treasureCardDeck, randomCards, 4);
		it->setHandCards(randomCards);
	}
}

void SoloGame::switchPlayer()
{
	actPlayerInx = (actPlayerInx >= 1) ? 0 : 1;
}