#pragma once

enum class SceneName
{
		MAIN_MENU,
		SOLO_GAME,
		START,
		STOP,
};

class Scene
{
	public:

		virtual void prepare() {};

		virtual void handleEvent() {};

		virtual void update() {};

		virtual void render() {};

		virtual void dispose() {}};
