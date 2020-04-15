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
	const char *const buttonText1 = "START THE GAME";
	const char *const buttonText2 = "OPTIONS";
	const char *const buttonText3 = "ABOUT";
	const char *const buttonText4 = "QUIT";


	/* -------------------- MAIN MENU ---------------- */
	const int menuButtonTextSize = 70;
	const int buttonsX = 205;
	const int buttonsY1 = 280;
	const int buttonsY2 = 380;
	const int buttonsY3 = 480;
	const int buttonsY4 = 580;




	const int fps = 60;
	const int minFrameTime = 1000.0f / fps;
}
