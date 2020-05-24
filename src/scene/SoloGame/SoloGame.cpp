#include "SoloGame.h"

SoloGame::SoloGame(SDLResources& inRes, SceneManager& inSceneManager) : res(inRes), sceneManager(inSceneManager)
{
}

void SoloGame::prepare()
{
	doorDeckGarbage = std::make_shared<CardDeck>();
	treasureDeckGarbage = std::make_shared<CardDeck>();
	doorCardDeck = std::make_unique<CardDeck>(doorDeckGarbage);
	treasureCardDeck = std::make_unique<CardDeck>(treasureDeckGarbage);

	readCards(constants::cardFile);
	doorCardDeckBack = std::make_unique<CardDeck>(*doorCardDeck);
	treasureCardDeckBack = std::make_unique<CardDeck>(*treasureCardDeck);
	gameBackground = std::make_unique<Background>(constants::gameWallpaperPath);
	SDL_Rect pos = {constants::playersX, constants::upPlayerY, 0, 0};

	std::vector<std::shared_ptr<Card>> randomCards;
	players.push_back(std::make_shared<Human>(randomCards, pos, res, doorDeckGarbage, treasureDeckGarbage));
	pos.y = constants::downPlayerY;
	players.push_back(std::make_shared<Human>(randomCards, pos, res, doorDeckGarbage, treasureDeckGarbage));
	players[0]->setOpp(players[1]);
	players[1]->setOpp(players[0]);
	setRandomPlayerCards();

	SDL_Rect buttonPos = {constants::pauseButtonX, constants::pauseButtonY, 0, 0};
	pauseButton = std::make_unique<GameButton>("PAUSE", buttonPos, res.menuFont);
	buttonPos.x = constants::actionButtonX;
	actionButton = std::make_unique<GameButton>(constants::actionButtonTexts[0], buttonPos, res.menuFont);
	monsterLevelInd = std::make_unique<Text>("POWER ", SDL_Rect({constants::monsterIndicatorX, constants::monsterIndicatorY}),
					res.gameFont, SDL_Color({255, 255, 255}), res.mainRenderer);
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
					//TODO: SAVE GAME
				}
			}
		}
		players[actPlayerInx]->handleEvent(event);
		pauseButton->handleEvent(event);
		actionButton->handleEvent(event);
		if (actPlayCard) actPlayCard->handleEvent(event);
	}
}

void SoloGame::update()
{
	// update player, check for win
	if (players[actPlayerInx]->getLevel() >= constants::winLevel)
	{
		int choice = winMenu();
		if (choice == 0)
			sceneManager.switchScene(SceneName::SOLO_GAME);
		else
			sceneManager.switchScene(SceneName::MAIN_MENU);
		return;
	}
	players[actPlayerInx]->update(actPlayCard, gameStateArr[actStateInx]);

	//handle pause button press
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
			//TODO: SAVE GAME
		}
	}

	// handle actual kicked card
	if (actPlayCard)
	{
		actPlayCard->update();
		if (actPlayCard->isMonster())
			monsterLevelInd->setText("POWER "+std::to_string(actPlayCard->combatPower()));
		if (gameStateArr[actStateInx] == GameState::KICK_DOORS)
			handleKicked();
	}

	// handle action button press
	if (actionButton->getState() == ButtonState::RELEASED)
	{
		handleActionButtonPress();
	}
}

void SoloGame::render()
{
	gameBackground->render(res.mainRenderer);
	for (auto& it: players)
		it->render(res.mainRenderer);
	pauseButton->render(res.mainRenderer);
	actionButton->render(res.mainRenderer);

	if (actPlayCard)
	{
		actPlayCard->render(res.mainRenderer);
		if (actPlayCard->isMonster()) monsterLevelInd->render(res.mainRenderer);
	}
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
	return dialogWin(buttons, SDL_arraysize(buttons), "Pause game.", "Game paused.");
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
		if (cardType == "curse")
		{
			int loseLevel;
			cardFile >> loseLevel;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
				doorCardDeck->addCard(std::make_shared<CurseCard>(cardPath.c_str(), defPos, helpText, loseLevel, res.gameFont));
		}

		else if (cardType == "monsterBoost")
		{
			int boostNum;
			cardFile >> boostNum;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
				doorCardDeck->addCard(std::make_shared<MonsterBoostCard>(cardPath.c_str(), defPos, helpText, boostNum, res.gameFont));
		}

		else if (cardType == "monster")
		{
			int monsterLevel, badStuffVal, treasures, giveLevels;
			std::string badStuff;
			cardFile >> monsterLevel;
			cardFile >> badStuff;
			cardFile >> badStuffVal;
			cardFile >> treasures;
			cardFile >> giveLevels;
			BadStuffType badStuffType = (badStuff == "level") ? BadStuffType::LEVEL : BadStuffType::CARDS;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
				doorCardDeck->addCard(std::make_shared<MonsterCard>(cardPath.c_str(), defPos, helpText, badStuffType,
								                                                   badStuffVal, monsterLevel, treasures, giveLevels, res.gameFont));
		}

		else if (cardType == "item")
		{
			std::string itemType;
			int combatBonus;
			cardFile >> combatBonus;
			cardFile >> itemType;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
				treasureCardDeck->addCard(std::make_shared<ItemCard>(cardPath.c_str(), defPos, helpText, combatBonus, res.gameFont));
		}

		else if (cardType == "levelup")
		{
			int level;
			cardFile >> level;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
				treasureCardDeck->addCard(std::make_shared<LevelUpCard>(cardPath.c_str(), defPos, helpText, level, res.gameFont));
		}

		else if (cardType == "boost")
		{
			int boost;
			cardFile >> boost;
			readHelp(cardFile, helpText);
			for (int i = 0; i < cardCount; i++)
				treasureCardDeck->addCard(std::make_shared<BoostCard>(cardPath.c_str(), defPos, helpText, boost, res.gameFont));
		}
	}
}

void SoloGame::restart()
{
	for (auto& it: players)
		it->setDefault();
	doorCardDeckBack->setDefault();
	treasureCardDeckBack->setDefault();
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
	{
		auto randCard = inCards->getCard();
		if (randCard->isMonster())
			i--;
		else
			outCards.push_back(randCard);
	}
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
	actPlayCard->changeButtons(false, true);
	if (actPlayCard->isMonster())
		monsterLevelInd->setText("POWER "+std::to_string(actPlayCard->combatPower()));
}

void SoloGame::handleKicked()
{
	actPlayCard->showHelp();
	if (actPlayCard->isMonster())
	{
		// switch to affect fight
		monsterLevelInd->setText("POWER "+std::to_string(actPlayCard->combatPower()));
		actStateInx++;
		std::string cantSwitch;
		switchPlayer(cantSwitch);
	}
	else if (actPlayCard->isCurse())
	{
		std::string retMessage;
		actPlayCard->play(players[actPlayerInx], actPlayCard, gameStateArr[actStateInx], retMessage);
		actStateInx += 3;
		doorDeckGarbage->addCard(actPlayCard);
		actPlayCard = nullptr;
	}
	else
	{
		actPlayCard->changeButtons(true, true);
		players[actPlayerInx]->gotCard(actPlayCard);
		actPlayCard = nullptr;
		actStateInx += 3;
	}
	actionButton->setText(constants::actionButtonTexts[actStateInx]);
}

void SoloGame::setRandomPlayerCards()
{
	std::vector<std::shared_ptr<Card>> randomCards;

	for (auto& it: players)
	{
		randomCards.clear();
		getRandomCards(doorCardDeck, randomCards, constants::startCardDoor);
		getRandomCards(treasureCardDeck, randomCards, constants::startCardTreasure);
		it->setHandCards(randomCards);
	}
}

bool SoloGame::switchPlayer(std::string& cantEndTurn)
{
	if (gameStateArr[actStateInx] == GameState::END_TURN)
	{
		if (!players[actPlayerInx]->endTurn(cantEndTurn))
			return false;
	}
	players[actPlayerInx]->endTurn();
	actPlayerInx = (actPlayerInx >= 1) ? 0 : 1;
	players[actPlayerInx]->startTurn();
	return true;
}

void SoloGame::handleFight()
{
	if (players[actPlayerInx]->getCombatPower() > actPlayCard->combatPower())
	{
		std::string defeatMonsterMess = "You defeated that monster. You will get "+std::to_string(actPlayCard->getTreasures())+" treasures"
																		" and "+std::to_string(actPlayCard->getLevels())+" levels.";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Defeated monster", defeatMonsterMess.c_str(), res.mainWindow);
		players[actPlayerInx]->resetBoost();
		players[actPlayerInx]->changeLevel(actPlayCard->getLevels());
		for (int i = 0; i < actPlayCard->getTreasures(); i++)
			players[actPlayerInx]->gotCard(treasureCardDeck->getCard());
		actStateInx++;
		doorDeckGarbage->addCard(actPlayCard);
		actPlayCard = nullptr;
		actionButton->setText(constants::actionButtonTexts[actStateInx]);
	}
	else
	{
		//monster is not defeated
		std::string loseMonsterMess = "You will loose against this monster.\nYou will have to roll a dice: "
																"youRolled > 5 - means you successfully ran away, otherwise that monster caught you and the bad thing will happen.";
		const SDL_MessageBoxButtonData buttons[] = {
						{ /* .flags, .buttonid, .text */        0, 0, "BACK" },
						{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "RUN AWAY" },
		};
		if (dialogWin(buttons, SDL_arraysize(buttons), "Run away", loseMonsterMess.c_str()) == 1)
		{
			runAway();
		}
	}
}

int SoloGame::dialogWin(const SDL_MessageBoxButtonData buttons[], int size, const char* title, const char* message)
{
	const SDL_MessageBoxColorScheme colorScheme = {
					{
									{ 186, 112, 0 },
									{   255, 255, 255 },
									{ 255, 255, 0 },
									{   41, 57, 201 },
									{ 255, 0, 255 }
					}
	};
	const SDL_MessageBoxData messageBoxData = {SDL_MESSAGEBOX_INFORMATION,nullptr,title,
	                                           message, size, buttons, &colorScheme };
	int buttonID;
	if (SDL_ShowMessageBox(&messageBoxData, &buttonID) < 0)
	{
		std::string erMessage = "Unable to pop up message box"; erMessage += SDL_GetError();
		throw SDLError(erMessage);
	}

	return buttonID;
}

void SoloGame::runAway()
{
	// TODO: graphic
	if (randomInt(1, 6) > 4)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Run Away", "You successfully ran away from that monster.",
		                         res.mainWindow);
	}
	else
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Run Away", "Monster caught you and bad thing will happen.",
		                         res.mainWindow);
		std::string dummy;
		actPlayCard->play(players[actPlayerInx], actPlayCard, gameStateArr[actStateInx], dummy);
	}
	players[actPlayerInx]->resetBoost();
	actStateInx++;
	actPlayCard->setDefault();
	doorDeckGarbage->addCard(actPlayCard);
	actPlayCard = nullptr;
	actionButton->setText(constants::actionButtonTexts[actStateInx]);
}

void SoloGame::handleActionButtonPress()
{
	std::string cantEndTurnText = "Can't end turn: ";
	switch (actStateInx)
	{
		case 0:
			kickDoor();
			break;

		case 1:
			actStateInx++;
			actionButton->setText(constants::actionButtonTexts[actStateInx]);
			players[actPlayerInx]->endTurn();
			switchPlayer(cantEndTurnText);
			break;

		case 2:
			//end fight
			handleFight();
			break;

		case 3:
			//end turn
			//some checks if player can end turn
			//pack pile if unpacked
			if (switchPlayer(cantEndTurnText))
			{
				actStateInx = 0;
				actionButton->setText(constants::actionButtonTexts[actStateInx]);
			}
			else
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Can't end turn!", cantEndTurnText.c_str(), res.mainWindow);
			break;
	}
	actionButton->setDefault();
}

int SoloGame::winMenu()
{
	std::string winMess;
	winMess = actPlayerInx ? "Bottom" : "Upper";
	winMess += " player win!";
	const SDL_MessageBoxButtonData buttons[] = {
					{ /* .flags, .buttonid, .text */        0, 0, "RESTART" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "BACK TO MENU" },
	};
	return dialogWin(buttons, SDL_arraysize(buttons), "End of the game.", winMess.c_str());
}
