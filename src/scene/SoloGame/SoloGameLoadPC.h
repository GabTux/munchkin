#include "SoloGame1vPC.h"
#include "../../game/Bot.h"

class SoloGameLoadPC : public SoloGame1vPC
{
	public:
		SoloGameLoadPC(SDLResources& inRes, SceneManager& inSceneManager);

		void setStartingState() override;
};