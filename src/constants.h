//
// Constants that cannot be changed by settings
//

#pragma once

namespace constants
{

	/* ------------------------------------- PATHS ---------------------------- */
	const char *const menuSelectorPath = "src/images/small_figure.bmp";
	const char *const menuWallpaperPath = "src/images/munchkin_wallpaper_1200_900.bmp";
	const char *const configFilePath = "configFile.txt";
	const char *const gameWallpaperPath = "src/images/wallpaper_game.bmp";
	const char *const menuButtonFontPath = "src/files/UbuntuMono-B.ttf";
	const char *const iconPath = "src/images/icon.bmp";

	/* ------------------------------------ GAME TEXTS ------------------------ */

	/* -------------------- MAIN MENU ---------------- */
	const int menuButtonTextSize = 70;
	const int mainMenuButtonsY[] = { 280, 380, 480, 580 };
	const int mainMenuButtonsX = 205;
	const char *const mainMenuButtonsText[] = { "ZAČÍT HRÁT", "NASTAVENÍ", "O HŘE", "UKONČIT"};
	const int mainMenuSelectorWidth = 50;
	const int mainMenuSelectorHeight = 65;
	const int mainMenuSelectorSpace = 70;

	/* -------------------- GAME MENU ---------------- */
	const char *const gameMenuButtonsText[] = {"NOVÁ HRA VS PC", "NOVÁ HRA 1v1", "ULOŽENÉ HRY", "ZPĚT"};

	const int fps = 60;
	const int minFrameTime = 1000.0f / fps;
}
