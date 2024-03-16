// main_menu.h

#pragma once

std::string loc_prompt = R"END({
    "root": {
        "type": "root",
        "pos": [ 0, 0 ],
        "size": [ "root_x", "root_x" ],
        "children": [
            {
                "play_against_grid": {
                    "cells": "1==;=2=;==3;=4=;5==",

                    "type": "grid",
                    "pos": [ 0, 0 ],
                    "size": [ "root_x", "root_x" ],
                    "children": []
                },
                "status_lbl_2": {
                    "text": "s2_text",

                    "type": "label",
                    "pos": [ 1, 10 ],
                    "size": [ 30, 1 ],
                    "children": []
                }
            }
        ]
    }
})END";

void sc_main_menu() {
    short arrow_pointer = 1;
    if( cross_screen_buffer.find("main_menu_ap") != cross_screen_buffer.end() ){
        arrow_pointer = cross_screen_buffer["main_menu_ap"];
    }

    auto arrow_pointer_op{
        [&arrow_pointer](short p){ if(arrow_pointer==p){ return std::wstring{L">"}; }else{ return std::wstring{L" "}; } }
    };

    bool run = true;
    while (run) {
        // drawing:
        clear();
        std::map<std::string, std::wstring> params = {
            //{"k_a1", wcat(arrow_pointer_op(1), L"start")},
            //{"k_a2", wcat(arrow_pointer_op(2), L"options")},
            //{"k_a3", wcat(arrow_pointer_op(3), L"quit")},
            {"root_x", std::to_wstring(settings.w) },
            {"root_y", std::to_wstring(settings.h) }
        };


        std::wcout << rendering(loc_prompt, params);
        //std::wcout << rendering(read_file("screens/main_menu.sc"), params);

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
