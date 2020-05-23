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
	TTF_CloseFont(res.gameFont);
	Mix_HaltMusic();
	Mix_FreeMusic(res.actualMusic);
	Mix_CloseAudio();

	Mix_Quit();
	SDL_Quit();
	TTF_Quit();
}

void Stop::update()
{
	sceneManager.stopGame();
}
