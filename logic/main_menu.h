// main_menu.h

#pragma once

void sc_main_menu() {
    short arrow_pointer = 1;
    if( cross_screen_buffer.find("main_menu_ap") != cross_screen_buffer.end() ){
        arrow_pointer = cross_screen_buffer["main_menu_ap"];
    }

    auto arrow_pointer_op{
        [&arrow_pointer](short p){ if(arrow_pointer==p){ return ">"; }else{ return " "; } }
    };

    bool run = true;
    while (run) {
        // drawing:
        clear();
        std::map<std::string, std::string> params = {
            {"k_a1", cat(arrow_pointer_op(1), "start")},
            {"k_a2", cat(arrow_pointer_op(2), "options")},
            {"k_a3", cat(arrow_pointer_op(3), "quit")},
            {"root_x", std::to_string(settings.w) },
            {"root_y", std::to_string(settings.h) }
        };

        std::cout << rendering(read_file("screens/main_menu.sc"), params);

        // input catching:
        switch ((int)wait_key_press()) {
            case ARROW_UP:
                if(arrow_pointer>1){arrow_pointer -= 1;}
            break;
            case ARROW_DOWN:
                if(arrow_pointer<3){arrow_pointer += 1;}
            break;
            case KEY_ENTER:
                switch (arrow_pointer) {
                    case 1:
                        cur_menu_num = PREPARING;
                        cross_screen_buffer["main_menu_ap"] = 1;
                        run = false;
                        break;
                    case 2:
                        cur_menu_num = OPTIONS;
                        cross_screen_buffer["main_menu_ap"] = 2;
                        run = false;
                        break;
                    case 3:
                        cur_menu_num = QUIT;
                        run = false;
                        break;
                }
            break;
        }
    }
}
