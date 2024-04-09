// global.h
// settings, global vars, constants and singletons
#pragma once
#include <string>
#include <map>



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
	{"roomfloor", "."},
	//{"door", "+"},
	{"corridor", "#"},
	{"upstairs", ">"},
	{"downstairs", "<"}
};
std::map<std::string, std::string> chmap_items{ // id, symbol
	{"gold", "$"},
	{"trap", "^"},
	{"weapon", ")"},
	{"armor", "["},
	{"eat", "%"},
	{"scroll", "?"},
	{"wand", "/"},
	{"ring", "="},
	{"potion", "!"},
	{"item", "("},
	{"amulet", "\""},
	{"stone", "*"},
	{"statue", "'"},
	{"ball", "0"},
	{"altar", "_"},
	{"fountain", "{"},
	{"pool", "}"},
	{"throne", "\\"}
};
std::map<std::string, std::string> chmap_creature{ // id, symbol
	{"player", "@"},
	{"ant", "a"},
	{"blob", "b"},
	{"dwarf", "d"},
	{"dragon", "D"},
	{"eye", "e"},
	{"elemental", "E"},
	{"goblin", "g"},
	{"gnom", "G"},
	{"imp", "i"},
	{"kobold", "k"},
	{"mimic", "m"},
	{"orc", "o"},
	{"spider", "s"},
	{"snake", "S"},
	{"unicorn", "u"},
	{"vortex", "v"},
	{"vampire", "V"},
	{"worm", "w"},
	{"xan", "x"},
	{"zombi", "z"}
};
std::string symbol_in(std::string simbol){
	std::string res = "unknown";
	for (const auto& pair : chmap_creature){
		if(simbol == pair.second){res="floor";}
	}
	for (const auto& pair : chmap_creature){
		if(simbol == pair.second){res="items";}
	}
	for (const auto& pair : chmap_creature){
		if(simbol == pair.second){res="creature";}
	}

	return res;
}

const int min_h=20, max_h=60, min_w=100, max_w=230;

// ------ global vars ------
int cur_menu_num = MAIN_MENU;
std::map<std::string, int> cross_screen_buffer;
std::vector<std::string> jornal;
unsigned long entityCounter = 0;

// ------ settings ------
#include "classes/Settings.h"
Settings settings;
/*	contain:
	"window_h" - hight
	"window_w" - width
*/

// ------ game morld ------
json jstats;
#include "classes/World.h"
World cur_world; // current deserialized world
