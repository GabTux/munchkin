#pragma once

#include <vector>

#include "../Scene.h"
#include "../Background.h"
#include "../SDLResources.h"
#include "../SceneManager.h"
#include "../../constants.h"
#include "../../game/cards/Card.h"

/**
 * Scene for game.
 */
class SoloGame : public Scene
{
	private:
		std::unique_ptr<Background> gameBackground;
		SDLResources& res;
		SceneManager& sceneManager;
		std::vector<std::shared_ptr<Card>> allCards;

		/**
		 * Try to read all cards from file.
		 * @param fileName path to txt file with list of cards.
		 */
		void readCards(const char * const fileName);

	public:
		/**
		 * Construct game scene.
		 * @param inRes reference to used SDL resources.
		 * @param inSceneManager reference to scene manager.
		 */
		SoloGame(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Init all used content.
		 */
		void prepare() override;

		/**
		 * Handle user input.
		 */
		void handleEvent() override;

		/**
		 * Render actual game status.
		 */
		void render() override;
};
