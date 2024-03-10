// global.h
// settings, global vars, constants and singletons
#pragma once
#include <string>
#include <map>



// ------ constants ------
const std::string settings_path = "settings.txt";
enum{
	KEY_ESC		= 27,
	KEY_ENTER	= 13,
	ARROW_UP	= 72,
	ARROW_DOWN	= 80,
	ARROW_LEFT	= 75,
	ARROW_RIGHT	= 77
};
enum{
	QUIT		= -1,
	MAIN_MENU	= 1,
	OPTIONS		= 2,
	PREPARING	= 3,
	DUNGEON		= 4
};
const int min_h=20, max_h=60, min_w=100, max_w=230;

// ------ global vars ------
int cur_menu_num = MAIN_MENU;
std::map<std::string, int> cross_screen_buffer;
unsigned long tid = 0;

// ------ settings ------
#include "classes/Settings.class"
Settings settings;/*
	contain:
	"window_h" - hight
	"window_w" - width
*/

// ------ game morld ------
#include "classes/World.class"
World cur_world; // current deserialized world
