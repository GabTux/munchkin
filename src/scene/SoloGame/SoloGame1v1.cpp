#include "SoloGame1v1.h"

SoloGame1v1::SoloGame1v1(SDLResources& inRes, SceneManager& inSceneManager) : SoloGame(inRes, inSceneManager)
{
}

void SoloGame1v1::prepare()
{
	SoloGame::prepare();
	SDL_Rect pos = {constants::playersX, constants::upPlayerY, 0, 0};
	std::vector<std::shared_ptr<Card>> randomCards;
	players.push_back(std::make_shared<Human>(randomCards, pos, res, doorDeckGarbage, treasureDeckGarbage));
	pos.y = constants::downPlayerY;
	players.push_back(std::make_shared<Human>(randomCards, pos, res, doorDeckGarbage, treasureDeckGarbage));
	players[0]->setOpp(players[1]);
	players[1]->setOpp(players[0]);
	setRandomPlayerCards();
	players[actPlayerInx]->startTurn();
}

void SoloGame1v1::handleEvent()
{
	SDL_Event event;
	while (!stopped && SDL_PollEvent(&event))
	{
		actionButton->handleEvent(event);
		SoloGame::handleEvent(event);
	}
}

void SoloGame1v1::looseAgainstMonster()
{
	std::string loseMonsterMess = "You will loose against this monster.\nYou will have to roll a dice: "
	                              "youRolled > 5 - means you successfully ran away, otherwise that monster caught you and the bad thing will happen.";
	const SDL_MessageBoxButtonData buttons[] = {
					{ /* .flags, .buttonid, .text */        0, 0, "BACK" },
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "RUN AWAY" },
	};
	if (dialogWin(buttons, SDL_arraysize(buttons), "Run away", loseMonsterMess.c_str()) == 1)
	{
		runAway("You successfully ran away, from that monster.", "Monster caught you and bad thing will happen.");
	}
}

void SoloGame1v1::checkForWinner()
{
	if (players[actPlayerInx]->getLevel() >= constants::winLevel)
	{
		int choice;
		if (actPlayerInx == 0)
			choice = winMenu("Upper player win!");
		else
			choice = winMenu("Bottom player win!");
		if (choice == 0)
		{
			stopScene();
			restart();
		}
		else
			sceneManager.switchScene(SceneName::MAIN_MENU);
	}
}
