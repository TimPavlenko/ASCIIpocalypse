// dungeon.h

#pragma once

void sc_dungeon() {
    print("dungeon!");
    const int sep_indent = 3; // отступ снизу
    std::string loc_prompt = R"END({
        "root": {
            "type": "root",
            "pos": [ 0, 0 ],
            "size": [ "rsizex", "rsizey" ],
            "children": [
                {
                    "play_against_grid": {
                        "cells": "pa_grid_text",

                        "type": "grid",
                        "pos": [ 0, 0 ],
                        "size": [ "pa_grid_sizex", "pa_grid_sizey" ],
                        "children": []
                    },
                    "sep_lbl": {
                        "text": "sep_lbl_text",

                        "type": "label",
                        "pos": [ 0, "sep_lbl_posy" ],
                        "size": [ "sep_lbl_sizex", 1 ],
                        "children": []
                    },
                    "status_lbl_1": {
                        "text": "s1_text",

                        "type": "label",
                        "pos": [ 1, "1s_lbl_posy" ],
                        "size": [ 30, 1 ],
                        "children": []
                    },
                    "status_lbl_2": {
                        "text": "s2_text",

                        "type": "label",
                        "pos": [ 1, "2s_lbl_posy" ],
                        "size": [ 30, 1 ],
                        "children": []
                    }
                }
            ]
        }
    })END";

    bool run = true;
    while (run) {
        // Формирование play_against_greed:
        std::wstring pa_greed_cells = L"rar!;rer!!";//L"map...  ;и русский язык!";
        //pa_greed_cells = "#   # ##### #   #  ##;#  ##   #   ## ## #  #;# # #   #   # # # #  #;##  #   #   #   # #  #;#   #   #   #   #  ##";
        /*std::vector<std::vector<std::string>> pa_greed_cells_v = cur_world.get_str(0);
        for(int iy=0; iy<10; iy++){
            for(int ix=0; ix<10; ix++){
                pa_greed_cells += pa_greed_cells_v[iy][ix];
            }
            //print(pa_greed_cells);
            pa_greed_cells += ";";
        }*/

        // Статусбар:
        std::wstring sep_buff = L"";
        for(int i=0; i<settings.w; i++){ sep_buff+=L"_"; }
        std::wstring status_line_1 = L"HP: "+wrem(7, L"46/50")+L"$: 10";
        std::wstring status_line_2 = L"XP: "+wrem(7, L"20/100");

        std::map<std::string, std::wstring> params = {
            {"rsizex", std::to_wstring(settings.w) },
            {"rsizey", std::to_wstring(settings.h) },
            {"sep_lbl_posy", std::to_wstring(settings.h-sep_indent) },
            {"sep_lbl_sizex", std::to_wstring(settings.w) },
            {"sep_lbl_text", sep_buff },
            {"s1_text", status_line_1 },
            {"1s_lbl_posy", std::to_wstring(settings.h-sep_indent+1) },
            {"s2_text", status_line_2 },
            {"2s_lbl_posy", std::to_wstring(settings.h-sep_indent+2) },
            {"pa_grid_sizex", std::to_wstring(settings.w-1) },
            {"pa_grid_sizey", std::to_wstring(settings.h-sep_indent) },
            {"pa_grid_text",  pa_greed_cells}
        };

        clear();
        std::wcout << L"Unicode -- English -- Русский -- Ελληνικά -- Español. \u9774 \u0444!" << std::endl;
        std::wcout << rendering(loc_prompt, params);

        cross_screen_buffer["PlayerCom"] = 0;
        // input catching:
        switch ((int)wait_key_press()) {
            case ARROW_UP:
                cross_screen_buffer["PlayerCom"] = 1;
            break;
            case ARROW_DOWN:
                cross_screen_buffer["PlayerCom"] = 2;
            break;
            case ARROW_LEFT:
                cross_screen_buffer["PlayerCom"] = 3;
            break;
            case ARROW_RIGHT:
                cross_screen_buffer["PlayerCom"] = 4;
            break;
            case KEY_ENTER:

            break;
        }
        //cur_world.tick(cur_world);
    }
}
