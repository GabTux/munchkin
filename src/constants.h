#pragma once

/**
 * Constants used across whole program.
 */
namespace constants
{

	/* ------------------------------------- WINDOW CONSTANTS ----------------- */
	const int windowWidth = 1200;
	const int windowHeight = 900;

	/* ------------------------------------- PATHS ---------------------------- */
	const char *const menuSelectorPath = "images/small_figure.bmp";
	const char *const menuWallpaperPath = "images/munchkin_wallpaper_1200_900.bmp";
	const char *const gameWallpaperPath = "images/wallpaper_game_1200_900.bmp";
	const char *const aboutWallpapers[] = { "images/figure_treasure.bmp", "images/figure_treasure_2.bmp" };
	const char *const menuButtonFontPath = "files/UbuntuMono-B.ttf";
	const char *const menuMusic = "sound/DEAF KEV - Invincible _NCS Release_.mp3";
	const char *const evilLaughs[] = { "sound/Evil_Laugh_1.wav", "sound/Evil_Laugh_2.wav", "sound/Evil_Laugh_3.wav" };
	const char *const iconPath = "images/icon.bmp";

	/* -------------------- MAIN MENU ---------------- */
	const int menuButtonTextSize = 70;
	const int mainMenuButtonsY[] = { 280, 380, 480 };
	const int mainMenuButtonsX = 205;
	const char *const mainMenuButtonsText[] = { "START THE GAME", "ABOUT", "QUIT"};
	const int mainMenuSelectorWidth = 50;
	const int mainMenuSelectorHeight = 65;
	const int mainMenuSelectorSpace = 70;

	/* -------------------- GAME MENU ---------------- */
	const int gameMenuButtonsY[] = { 280, 380, 480, 580 };
	const char *const gameMenuButtonsText[] = {"NEW GAME VS PC", "NEW GAME 1v1", "SAVED GAMES", "BACK"};

	/* -------------------- ABOUT ---------------- */
	const int backButtonX = 1000;
	const int backButtonY = 820;
	const char * const backButtonText = "BACK";
	const char * const aboutText = "Super Munchkin\nVersion: 0.24\nC++ and SDL2\nGabriel Hévr © 2020";
	const int aboutTextX = 500;
	const int aboutTextY = 500;

		const int fps = 60;
	const int minFrameTime = 1000.0f / fps;
}
