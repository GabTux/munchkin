#include "SoloGame.h"

SoloGame::SoloGame(SDLResources& inRes, SceneManager& inSceneManager) : sceneManager(inSceneManager), res(inRes)
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

	SDL_Rect buttonPos = {constants::pauseButtonX, constants::pauseButtonY, 0, 0};
	pauseButton = std::make_unique<GameButton>("PAUSE", buttonPos, res.menuFont);
	buttonPos.x = constants::actionButtonX;
	actionButton = std::make_unique<GameButton>(constants::actionButtonTexts[0], buttonPos, res.menuFont);
	monsterLevelInd = std::make_unique<Text>("POWER ", SDL_Rect({constants::monsterIndicatorX, constants::monsterIndicatorY}),
					res.gameFont, SDL_Color({255, 255, 255}), res.mainRenderer);
}

void SoloGame::handleEvent(SDL_Event& event)
{
	if (stopped)
		return;

	if (event.type == SDL_QUIT)
	{
		sceneManager.switchScene(SceneName::STOP);
		return;
	}

	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			handlePauseMenu();
		}
	}
	players[actPlayerInx]->handleEvent(event);
	pauseButton->handleEvent(event);
	if (actPlayCard) actPlayCard->handleEvent(event);
}

void SoloGame::update()
{
	checkForWinner();
	players[actPlayerInx]->update(actPlayCard, gameStateArr[actStateInx]);

	//handle pause button press
	if (pauseButton->getState() == ButtonState::RELEASED)
	{
		handlePauseMenu();
	}

	// handle actual kicked card
	if (actPlayCard)
	{
		actPlayCard->update();
		if (actPlayCard->isMonster())
			monsterLevelInd->setText("POWER "+std::to_string(actPlayCard->getCombatPower()));
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
	Card::resetCounter();
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
	pauseButton->setDefault();
	actionButton->setText(constants::actionButtonTexts[0]);
	actionButton->setDefault();
	stopped = false;

	setStartingState();
}

void SoloGame::getRandomCards(std::unique_ptr<CardDeck>& inCards, std::vector<std::shared_ptr<Card>>& outCards, int count)
{
	for (int i = 0; i < count; i++)
	{
		auto randCard = inCards->getCard();
		if (randCard->isMonster())
		{
			doorDeckGarbage->addCard(randCard);
			i--;
		}
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
		monsterLevelInd->setText("POWER "+std::to_string(actPlayCard->getCombatPower()));
}

void SoloGame::handleKicked()
{
	actPlayCard->showHelp();
	if (actPlayCard->isMonster())
	{
		// switch to affect fight
		monsterLevelInd->setText("POWER "+std::to_string(actPlayCard->getCombatPower()));
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

void SoloGame::setStartingState()
{
	std::vector<std::shared_ptr<Card>> randomCards;

	for (auto& it: players)
	{
		randomCards.clear();
		getRandomCards(doorCardDeck, randomCards, constants::startCardDoor);
		getRandomCards(treasureCardDeck, randomCards, constants::startCardTreasure);
		it->setHandCards(randomCards);
	}

	actPlayerInx = 0;
	actStateInx = 0;
	actPlayCard = nullptr;
	players[actPlayerInx]->startTurn();
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
	if (players[actPlayerInx]->getCombatPower() > actPlayCard->getCombatPower())
	{
		std::string defeatMonsterMess;
		if (againstBot && actPlayerInx == 0)
			defeatMonsterMess = "Bot defeated that monster. He will get "+std::to_string(actPlayCard->getTreasures())+" treasures"
																			" and "+std::to_string(actPlayCard->getLevels())+" levels.";
		else
			defeatMonsterMess = "You defeated that monster. You will get "+std::to_string(actPlayCard->getTreasures())+" treasures"
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
		looseAgainstMonster();
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

void SoloGame::runAway(const char * ranAway, const char * noRanAway)
{
	// TODO: graphic
	if (randomInt(1, 6) > 4)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Run Away", ranAway,
		                         res.mainWindow);
	}
	else
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Run Away", noRanAway,
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

int SoloGame::winMenu(const char * text) const
{
	const SDL_MessageBoxButtonData buttons[] = {
					{ /* .flags, .buttonid, .text */        0, 0, "RESTART" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "BACK TO MENU" },
	};
	return dialogWin(buttons, SDL_arraysize(buttons), "End of the game.", text);
}

bool SoloGame::saveToFile()
{
	std::string saveFilePath = std::filesystem::current_path().string();
	saveFilePath += "/"+std::string(constants::saveFolder);
	if (!std::filesystem::is_directory(saveFilePath) && !std::filesystem::create_directory(saveFilePath))
		return false;

	saveFilePath += againstBot ? constants::saveNames[0] : constants::saveNames[1];
	std::ofstream saveFile(saveFilePath);
	if (!saveFile.is_open())
		return false;

	for (auto & it: players)
		saveFile << *it;
	if (!saveFile.good())
		return false;

	saveFile << *doorDeckGarbage;
	if (!saveFile.good())
		return false;

	saveFile << *treasureDeckGarbage;
	if (!saveFile.good())
		return false;

	saveFile << actPlayerInx << " " << actStateInx << " ";
	if (!saveFile.good())
		return false;

	if (actPlayCard)
	{
		saveFile << (actPlayCard->isTreasure() ? 't' : 'd');
		if (!saveFile.good())
			return false;

		saveFile << " " << actPlayCard->getID() << " " << -1 << std::endl;
	}
	else
		saveFile << 'd' << -2 << std::endl;

	saveFile.close();
	return saveFile.good();
	//TODO: check if normal decks are same
}

void SoloGame::handlePauseMenu()
{
	int choice = pauseMenu();       //this will block current thread until messagebox resolved
	if (choice == 2)
	{
		//BACK TO MENU
		sceneManager.switchScene(SceneName::MAIN_MENU);
		return;
	}

	if (choice == 1)
	{
		// SAVE GAME
		if (!saveToFile())
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot save file",
			                         "Cannot save file.\nProbably insufficient permissions.", res.mainWindow);
		}
		else
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Saved.", "Game saved.", res.mainWindow);
	}
}

bool SoloGame::loadFromFile(std::ifstream& inFile, std::string& errMess)
{
	// load players
	if (!loadPlayers(inFile, errMess))
		return false;

	// load garbage decks
	if (!loadGarbageDecks(inFile, errMess))
		return false;

	// set game states
	inFile >> actPlayerInx;
	if (!inFile.good() || actPlayerInx > 1 || actPlayerInx < 0)
	{
		errMess += "file corrupted";
		return false;
	}

	inFile >> actStateInx;
	if (!inFile.good() || actStateInx > 4 || actStateInx < 0)
	{
		errMess += "file corrupted";
		return false;
	}

	char deckID;
	int idCard;
	inFile >> deckID;
	inFile >> idCard;
	if (!inFile.good())
		return false;
	if (idCard != -2 && !moveCard(deckID, idCard, actPlayCard, errMess))
	{
		errMess += "Missing card";
		return false;
	}

	for (auto &it: players)
		it->updateIndicators();
	actionButton->setText(constants::actionButtonTexts[actStateInx]);
	if (actPlayCard)
	{
		SDL_Rect actPos = {constants::actCardX, constants::actCardY, 0, 0};
		actPlayCard->setPosition(actPos);
		actPlayCard->changeButtons(false, true);
	}

	return true;
}

bool SoloGame::loadPlayers(std::ifstream& inFile, std::string& errMess)
{
	// set player hands+inv
	std::vector<std::shared_ptr<Card>> loadedCards;
	std::shared_ptr<Card> outCard;
	int tmpLevel;

	for (auto& it: players)
	{
		inFile >> tmpLevel;
		if (!inFile.good())
		{
			errMess += "File corrupted";
			return false;
		}
		it->changeLevel(tmpLevel-1);

		for (int i = 0; i < 2; i++)
		{
			loadedCards.clear();
			int idCard;
			char deckID;
			while (true)
			{
				inFile >> deckID;
				inFile >> idCard;
				if (!inFile.good())
					return false;
				if (idCard == -1)
					break;
				if (!moveCard(deckID, idCard, outCard, errMess))
					return false;
				else
					loadedCards.push_back(outCard);
			}
			if (i == 0)
				it->setHandCards(loadedCards);
			else
				it->setInvCards(loadedCards);
		}
	}
	return true;
}

bool SoloGame::moveCard(char deckID, int idCard, std::shared_ptr<Card>& outCard, std::string& errMess)
{
	std::shared_ptr<Card> tmpCard;

	if (deckID == 'd')
	{
		if (!doorCardDeck->getCard(idCard, tmpCard))
		{
			errMess += "Missing Card";
			return false;
		}
	}
	else if (deckID == 't')
	{
		if (!treasureCardDeck->getCard(idCard, tmpCard))
		{
			errMess = "Missing card.";
			return false;
		}
	}
	else
	{
		errMess = "File is corrupted.";
		return false;
	}
	outCard = tmpCard;
	return true;
}

bool SoloGame::loadGarbageDecks(std::ifstream& inFile, std::string& errMess)
{
	char deckID = 'd';
	int idCard;
	std::shared_ptr<Card> outCard;

	for (int i = 0; i < 2; i++, deckID = 't')
	{
		while (true)
		{
			inFile >> idCard;
			if (!inFile.good())
				return false;
			if (idCard == -1)
				break;
			if (!moveCard(deckID, idCard, outCard, errMess))
				return false;
			if (deckID == 'd')
				doorDeckGarbage->addCard(outCard);
			else
				treasureDeckGarbage->addCard(outCard);
		}
	}
	return true;
}

