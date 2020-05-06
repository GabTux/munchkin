#pragma once

/*
 * All scene names.
 */
enum class SceneName
{
		MAIN_MENU,
		GAME_MENU,
		SOLO_GAME,
		START,
		STOP,
		ABOUT,
};

class Scene
{
	public:
		/**
		 * Prepare all used content for actual scene.
		 */
		virtual void prepare() {}

		/**
		 * Handle all used events.
		 */
		virtual void handleEvent() {}

		/**
		 * Update values according to events.
		 */
		virtual void update() {}

		/**
		 * Render new content.
		 */
		virtual void render() {}

		/**
		 * Dispose scene. Delete all used content to save memory.
		 */
		virtual void dispose() {}
};
