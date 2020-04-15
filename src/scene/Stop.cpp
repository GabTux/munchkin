#include "Stop.h"

Stop::Stop(SDLResources &inRes, SceneManager &inSceneManager) :
res(inRes), sceneManager(inSceneManager)
{
}

void Stop::prepare()
{
	SDL_DestroyRenderer(res.mainRenderer);
	SDL_DestroyWindow(res.mainWindow);

	TTF_CloseFont(res.menuFont);

	SDL_Quit();
	TTF_Quit();
}
// TODO: remove this angry comment
// the drivers are FUCKED UP and so it will always leaks memory


void Stop::update()
{
	sceneManager.finish();
}
