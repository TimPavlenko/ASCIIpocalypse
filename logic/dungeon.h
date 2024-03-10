// dungeon.h

#pragma once

void sc_dungeon() {
    print("dungeon!");
    const int sep_indent = 4; // отступ снизу
    std::string loc_prompt = R"END({
        "root": {
            "type": "root",
            "pos": [ 0, 0 ],
            "size": [ "rsizex", "rsizey" ],
            "parts": false,
            "children": [
                {
                    "play_against_greed": {
                        "cells": "pa_greed_text",

                        "type": "greed",
                        "pos": [ 0, 0 ],
                        "size": [ "pa_greed_sizex", "pa_greed_sizey" ],
                        "parts": true,
                        "children": []
                    },
                    "sep_lbl": {
                        "text": "sep_lbl_text",

                        "type": "label",
                        "pos": [ 0, "sep_lbl_posy" ],
                        "size": [ "sep_lbl_sizex", 1 ],
                        "parts": false,
                        "children": []
                    },
                    "status_lbl_1": {
                        "text": "s1_text",

                        "type": "label",
                        "pos": [ 0, "1s_lbl_posy" ],
                        "size": [ 30, 1 ],
                        "parts": false,
                        "children": []
                    },
                    "status_lbl_2": {
                        "text": "s2_text",

                        "type": "label",
                        "pos": [ 0, "2s_lbl_posy" ],
                        "size": [ 30, 1 ],
                        "parts": false,
                        "children": []
                    }
                }
            ]
        }
    })END";

    bool run = true;
    while (run) {
        // Формирование play_against_greed:
        std::string pa_greed_cells = "";
        //pa_greed_cells = "#   # ##### #   #  ##;#  ##   #   ## ## #  #;# # #   #   # # # #  #;##  #   #   #   # #  #;#   #   #   #   #  ##";
        pa_greed_cells = "12345;67890";
        /*for(int ix=0; ix<20; ix++){
            for(int iy=0; iy<10; iy++){
                pa_greed_cells += "#";//cur_world.grid[layer][ix][iy].get_str();
            }
            pa_greed_cells += ";";
        }*/

        // Статусбар:
        std::string sep_buff = "";
        for(int i=0; i<settings.w; i++){ sep_buff+="_"; }
        std::string status_line_1 = "HP: "+rem(7, "46/50");
        std::string status_line_2 = "XP: "+rem(7, "20/100");

        std::map<std::string, std::string> params = {
            {"rsizex", std::to_string(settings.w) },
            {"rsizey", std::to_string(settings.h) },
            {"sep_lbl_posy", std::to_string(settings.h-sep_indent) },
            {"sep_lbl_sizex", std::to_string(settings.w) },
            {"sep_lbl_text", sep_buff },
            {"s1_text", status_line_1 },
            {"1s_lbl_posy", std::to_string(settings.h-sep_indent+1) },
            {"s2_text", status_line_2 },
            {"2s_lbl_posy", std::to_string(settings.h-sep_indent+2) },
            {"pa_greed_sizex", std::to_string(settings.w) },
            {"pa_greed_sizey", std::to_string(settings.h-sep_indent) },
            {"pa_greed_text",  pa_greed_cells}
        };

        clear();
        std::cout << rendering(loc_prompt, params);

        // input catching:
        switch ((int)wait_key_press()) {
            case ARROW_UP:

            break;
            case ARROW_DOWN:

            break;
            case ARROW_LEFT:

            break;
            case ARROW_RIGHT:

            break;
            case KEY_ENTER:

            break;
        }
    }
}
