// global.h
// settings, global vars, constants and singletons
#pragma once
#include <string>
#include <map>
#include "classes/World.h"


// ------ constants ------
const std::string settings_path = "settings.txt";
enum{ // key codes
	KEY_ESC		= 27,
	KEY_ENTER	= 13,
	ARROW_UP	= 72,
	ARROW_DOWN	= 80,
	ARROW_LEFT	= 75,
	ARROW_RIGHT	= 77
};
enum{ // id экранов
	QUIT		= -1,
	MAIN_MENU	= 1,
	OPTIONS		= 2,
	PREPARING	= 3,
	DUNGEON		= 4
};
// символы для графики:
std::map<std::string, std::string> chmap_floor{ // id, symbol
	{"bedrock", " "},
	{"hwall", "-"},
	{"vwall", "|"},
	{"roomfloor", "."}
};

const int min_h=20, max_h=60, min_w=100, max_w=230;

// ------ global vars ------
int cur_menu_num = MAIN_MENU;
std::map<std::string, int> cross_screen_buffer;
std::vector<std::string> jornal;

// ------ settings ------
#include "classes/Settings.h"
Settings settings;
/*	contain:
	"window_h" - hight
	"window_w" - width
*/

// ------ game morld ------
World cur_world; // current deserialized world
