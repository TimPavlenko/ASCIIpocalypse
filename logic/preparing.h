// preparing.h

#pragma once

void sc_preparing() {
    short arrow_pointer = 1;

    auto arrow_pointer_op{
        [&arrow_pointer](short p){ if(arrow_pointer==p){ return std::string{">"}; }else{ return std::string{" "}; } }
    };

    bool run = true;
    while (run) {
        // drawing:
        std::map<std::string, std::string> params = {
            {"k_a1", cat(std::string{arrow_pointer_op(1)}, "let's do it")},
            {"k_a2", cat(std::string{arrow_pointer_op(2)}, "here will be; the character settings")},
            {"k_a3", cat(std::string{arrow_pointer_op(3)}, "back")},
            {"root_x", std::to_string(settings.w) },
            {"root_y", std::to_string(settings.h) }
        };
        clear();
        std::cout << rendering(read_file("screens/preparing.sc"), params);

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
                        cur_menu_num = DUNGEON;
                        run = false;
                        cur_world.gen(10, 10, 2);
                        break;
                    case 2:
                        print("2");
                        break;
                    case 3:
                        cur_menu_num = MAIN_MENU;
                        run = false;
                        break;
                }
            break;
        }
    }
}
