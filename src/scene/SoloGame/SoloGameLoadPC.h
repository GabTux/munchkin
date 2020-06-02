#include "SoloGame1vPC.h"
#include "../../game/Bot.h"

/**
 * Class for loading saved game against PC.
 */
class SoloGameLoadPC : public SoloGame1vPC
{
	public:
		/**
		 * Constructs new loaded game.
		 * @param inRes Reference to SDL resources.
		 * @param inSceneManager Reference to scene manager.
		 */
		SoloGameLoadPC(SDLResources& inRes, SceneManager& inSceneManager);

		/**
		 * Try to load game.
		 */
		void setStartingState() override;
};