#pragma once

/*
 * All scene names.
 */
enum class SceneName
{
		MAIN_MENU,
		GAME_MENU,
		SOLO_GAME_1vPC,
		SOLO_GAME_1v1,
		ABOUT,
		START,
		STOP
};

class Scene
{
	private:
		bool readyState = false;

	public:
		/**
		 * Wrapper around virtual function prepare.
		 * It calls overridden function prepare and sets state to ready.
		 */
		void makeReady();

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
		 * Restart scene.
		 * Set all content to starting state.
		 */
		virtual void restart() {}

		/**
		 * Stop running loops in actual scene.
		 * It is called before switching to another scene.
		 */
		virtual void stopScene() { }

		/**
		 * Get actual state of scene.
		 * @return true - ready, false - not ready.
		 */
		[[nodiscard]] bool ready() const { return readyState; }
};