
// ############## includ'ки ##############
// STL:
//#include "stdafx.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
// Custom:
#include "tims_header.h"


// ############## Global ##############
#include "global.h"


// ############## Funcs ##############
#include "funcs/saveload.h"
#include "funcs/platform.h"
#include "funcs/graphics.h"


// ############## Game Logic ##############
#include "logic/main_menu.h"
#include "logic/options.h"
#include "logic/preparing.h"
#include "logic/dungeon.h"


// ############## Main cycle ##############
int main() {
    // preparing:
    settings = Settings(load_map(settings_path));
    resize_window(settings.w, settings.h);

    // анотация перед запуском
    //std::cout<<"=- victim -="<<std::endl;
    //wait_key_press();

    // screens switcher:
    bool main_cycle_run = true;
    while (main_cycle_run){
        switch (cur_menu_num) {
        case MAIN_MENU:
            sc_main_menu();
            break;
        case OPTIONS:
            sc_options();
            break;
        case PREPARING:
            sc_preparing();
            break;
        case DUNGEON:
            sc_dungeon();
            break;
        default: /*unknown shit*/
            //print("unknown menu num!");
        case QUIT:
            settings.serialize(settings_path);
            main_cycle_run = false;
            break;
        }
    }
    clear();
    print("Goodbye, traveler");
    return 0;
}

#include "classes/Object.cpp"
#include "classes/Entity.cpp"
#include "classes/Floor.cpp"
