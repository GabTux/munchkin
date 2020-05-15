#include "SoloGame.h"

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
	SDL_Rect pos = {5, 5, 0, 0};
	std::vector<std::shared_ptr<Card>> randomCards;
	for (int i = 0; i < 4; i++)
	{
		randomCards.push_back(doorCardDeck->getCard());
		randomCards.push_back(treasureCardDeck->getCard());
	}
	pl1 = std::make_unique<Human>(randomCards, pos);
	randomCards.clear();
	for (int i = 0; i < 4; i++)
	{
		randomCards.push_back(doorCardDeck->getCard());
		randomCards.push_back(treasureCardDeck->getCard());
	}
	pos.y = 600;
	pl2 = std::make_unique<Human>(randomCards, pos);
	SDL_Rect pausePos = {10, 350, 0, 0};
	pauseButton = std::make_unique<GameButton>("PAUSE", pausePos, res.menuFont);
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
		pl1->handleEvent(event);
		pl2->handleEvent(event);
		pauseButton->handleEvent(event);
	}
}

void SoloGame::update()
{
	pl1->update();
	pl2->update();
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
}

void SoloGame::render()
{
	gameBackground->render(res.mainRenderer);
	pl1->render(res.mainRenderer);
	pl2->render(res.mainRenderer);
	pauseButton->render(res.mainRenderer);
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
	pl1->setDefault();
	pl2->setDefault();
	doorCardDeck = std::make_unique<CardDeck>(*doorCardDeckBack);
	treasureCardDeck = std::make_unique<CardDeck>(*treasureCardDeckBack);
	std::vector<std::shared_ptr<Card>> randomCards;
	getRandomCards(doorCardDeck, randomCards, 4);
	getRandomCards(treasureCardDeck, randomCards, 4);
	pl1->setHandCards(randomCards);
	randomCards.clear();
	getRandomCards(doorCardDeck, randomCards, 4);
	getRandomCards(treasureCardDeck, randomCards, 4);
	pl2->setHandCards(randomCards);

	pauseButton->setDefault();
	stopped = false;
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

