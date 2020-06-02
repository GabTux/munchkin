#pragma once

#include <vector>
#include <random>

#include "Scene.h"
#include "SceneManager.h"
#include "Background.h"
#include "../game/GameObject.h"
#include "Menu/MenuButton.h"
#include "../constants.h"
#include "../functions.h"

/**
 * Class for About scene.
 */
class About : public Scene
{
	private:
		SDLResources& res;
		SceneManager& sceneManager;
		std::unique_ptr<Background> mainBackground;
		std::unique_ptr<Background> mouthFunBackground;
		std::vector<std::unique_ptr<GameObject>> figures;
		std::unique_ptr<MenuButton> backButton;

		SDL_Color white = {255, 255, 255 };

		Uint32 startSpawnTime;
		Uint32 delaySpawnTime = randomInt(4000, 8000);

		Uint32 startBackTime;
		Uint32 delayBackTime = randomInt(2000, 5000);
		int mouthCycles;
		Uint32 mouthStart;
		Uint32 mouthDelay = 75;
		bool mouthOpen;
		bool mouthAction;
		Mix_Chunk* sLaugh = nullptr;

		SDL_Texture* aboutTexture = nullptr;
		SDL_Rect aboutTextPosition;

		bool stopped = false;

		/**
		 * Create new figure.
		 */
		void spawnFigure();

		/**
		 * Spawn new figures or delete one figure.
		 */
		void randomizeIt();

		/**
		 * Render background to ensure background animation.
		 */
		void renderBackgrounds();

	public:
		/**
		 * Construct about scene.
		 * @param inRes SDLResources, that will be initialized.
		 * @param inSceneManager Scene manager, used to switch to another scene.
	 	 */
		About(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Prepare figures.
		 */
		void prepare() override;

		/**
		 * Handle user input.
		 */
		void handleEvent() override;

		/**
		 * Move figures at random speed.
		 * Also spawn random figures.
		 */
		void update() override;

		/**
		 * Render all figures.
		 */
		void render() override;

		/**
		 * Clear all figures.
		 */
		void restart() override;

		/**
		 * Stop laugh cycles.
		 */
		void stopScene() override;

		/**
		 * Clean up local resources.
		 */
		~About();
};