#include "SoloGame1vPC.h"
#include "../../game/Bot.h"

SoloGame1vPC::SoloGame1vPC(SDLResources& inRes, SceneManager& inSceneManager) : SoloGame(inRes, inSceneManager)
{
	againstBot = true;
}

void SoloGame1vPC::prepare()
{
	SoloGame::prepare();
	SDL_Rect pos = {constants::playersX, constants::upPlayerY, 0, 0};
	std::vector<std::shared_ptr<Card>> randomCards;
	players.push_back(std::make_shared<Bot>(randomCards, pos, res, doorDeckGarbage, treasureDeckGarbage));
	pos.y = constants::downPlayerY;
	players.push_back(std::make_shared<Human>(randomCards, pos, res, doorDeckGarbage, treasureDeckGarbage));
	players[0]->setOpp(players[1]);
	players[1]->setOpp(players[0]);
	setStartingState();
	players[actPlayerInx]->startTurn();
}

void SoloGame1vPC::handleEvent()
{
  SDL_Event event;
	while (!stopped && SDL_PollEvent(&event))
	{
		if (actPlayerInx) actionButton->handleEvent(event);
		SoloGame::handleEvent(event);
	}
}

void SoloGame1vPC::update()
{
	SoloGame::update();
	if (players[0]->played())
	{
		SoloGame::handleActionButtonPress();
	}
}

void SoloGame1vPC::looseAgainstMonster()
{
	if (actPlayerInx == 1)
	{
		std::string loseMonsterMess = "You will loose against this monster.\nYou will have to roll a dice: "
		                              "youRolled > 5 - means you successfully ran away, otherwise that monster caught you and the bad thing will happen.";
		const SDL_MessageBoxButtonData buttons[] = {
						{ /* .flags, .buttonid, .text */        0,                                       0, "BACK"},
						{                                       SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "RUN AWAY"},
		};
		if (dialogWin(buttons, SDL_arraysize(buttons), "Run away", loseMonsterMess.c_str()) == 1)
		{
			runAway("You successfully ran away, from that monster.", "Monster caught you and bad thing will happen.");
		}
	}
	else
		runAway("Bot ran away from that monster.", "Bot could not ran away and that monster caught him.\n"
																						"Bad thing will happen to him.");
}

void SoloGame1vPC::checkForWinner()
{
	if (players[actPlayerInx]->getLevel() >= constants::winLevel)
	{
		int choice;
		if (actPlayerInx == 0)
			choice = winMenu("Muhahahahahaha, you lost. 8-)");
		else
			choice = winMenu("Congratz, you win.");
		if (choice == 0)
		{
			stopScene();
			restart();
		}
		else
			sceneManager.switchScene(SceneName::MAIN_MENU);
	}
}
