#pragma once

void sc_end() {
    const std::string asciiart_dead = "######_   ######   ___       ######_;|##- ###  ##   -  |####_     |##- ###;|##   ##|  ###    |##  -#_   |##   ##;|##_   #|  ##  _  |##____##  |##_   #;||##### |  |####  |##   ###| ||#####; ||#  | |  | ||   |||   #|#|  ||#  |; | |  |    | |    | |   || |  | |  |; | |  |      |      |   |     | |  |;   |         |    |     |  |    |; |                         |";
    const int asciiart_shift_d = 37;

    bool run = true;
    while (run) {
        int asciiart_shift = (settings.w-asciiart_shift_d)/2;

        // drawing:
        clear();
        std::map<std::string, std::string> params = {
            {"asciiart", asciiart_dead },
            {"asciiart_shift", std::to_string(asciiart_shift) },
            {"root_x", std::to_string(settings.w) },
            {"root_y", std::to_string(settings.h) }
        };

        std::cout << rendering(read_file("screens/end.sc"), params);

        switch ((int)wait_key_press()) {
        case KEY_ENTER:
            cur_menu_num = MAIN_MENU;
            run = false;
        break;
        }
    }
}
