// dungeon.h

#pragma once

void sc_dungeon() {
    const int hsep1_indent = 5; // отступ снизу (n-1 строк под разделителем)
    const int vsep1_indent = 50; // отступ справа (т-1) // ширина журнала
    std::string loc_prompt = R"END({
        "root": {
            "type": "root",
            "pos": [ 0, 0 ],
            "size": [ "rsizex", "rsizey" ],
            "children": [
                {
                    "jornal": {
                        "text": "jornal_text",

                        "type": "multiline",
                        "pos": [ "jornal_posx", 0 ],
                        "size": [ "jornal_sizex", "jornal_sizey" ],
                        "children": []
                    },
                    "play_against_grid": {
                        "cells": "pa_grid_text",

                        "type": "grid",
                        "pos": [ "pa_grid_posx", 0 ],
                        "size": [ "pa_grid_sizex", "pa_grid_sizey" ],
                        "children": []
                    },
                    "hsep1_lbl": {
                        "text": "hsep1_lbl_text",

                        "type": "label",
                        "pos": [ 0, "hsep1_lbl_posy" ],
                        "size": [ "hsep1_lbl_sizex", 1 ],
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
        std::string pa_greed_cells = "   - - - - -;   | @ . . |;   | . . . | ;   | . . . + # # #   - - - - -;   - - - - -     #   | . . . |;                 # # + . . . |;                 #   - - - - -;             - - + - - - ; - - - - -   | . . . . |; | . . . + # # . . . [ |; | > . . |   | . g . . |; - - - - -   | . . . . |;       	     - - - - - -";
        //std::string pa_greed_cells = cur_world.get_str();

        // формирование журнала:
        std::string jornal_text = "";
        std::vector<std::string> jornal_v_tmp = {};
        for(int i=0; i<settings.h; i++){
            if(i+1>jornal.size()){
                jornal_v_tmp.push_back(" ");
            }else{
                //jornal_v_tmp.push_back(jornal[i]);
                jornal_v_tmp.insert(jornal_v_tmp.begin(), jornal[i]);
            }
        }
        if(settings.reverse_jornal){ std::reverse( jornal_v_tmp.begin(), jornal_v_tmp.end() ); }
        for(int i=0; i<jornal_v_tmp.size(); i++){
            jornal_text+="| "+jornal_v_tmp[i];
            if(i<jornal_v_tmp.size()-1){ jornal_text+=";"; }
        }


        // Статусбар:
        std::string sep_buff = "";
        for(int i=0; i<settings.w-vsep1_indent; i++){ sep_buff+="_"; }
        std::string status_line_1 = "HP: "+rem(7, "46/50") +"AC: 10  "+"loc: 1-1";
        std::string status_line_2 = "XP: "+rem(7, "20/100")+"$: 45   "+"T: 27   ";

        std::map<std::string, std::string> params = {
            {"rsizex", std::to_string(settings.w) },
            {"rsizey", std::to_string(settings.h) },
            {"hsep1_lbl_posy", std::to_string(settings.h-hsep1_indent) },
            {"hsep1_lbl_sizex", std::to_string(settings.w) },
            {"hsep1_lbl_text", sep_buff },
            {"s1_text", status_line_1 },
            {"1s_lbl_posy", std::to_string(settings.h-hsep1_indent+1) },
            {"s2_text", status_line_2 },
            {"2s_lbl_posy", std::to_string(settings.h-hsep1_indent+2) },
            {"pa_grid_posx", std::to_string(/*hsep1_indent+1*/0) },
            {"pa_grid_sizex", std::to_string(settings.w-vsep1_indent) },
            {"pa_grid_sizey", std::to_string(settings.h-hsep1_indent) },
            {"pa_grid_text",  pa_greed_cells},
            {"jornal_posx", std::to_string(settings.w-vsep1_indent) }, // settings.w-2-hsep1_indent
            {"jornal_sizex", std::to_string(vsep1_indent) },
            {"jornal_sizey", std::to_string(settings.h) },
            {"jornal_text", jornal_text }
        };

        clear();
        //std::wcout << L"Unicode -- English -- Русский -- Ελληνικά -- Español. \u9774 \u0444!" << std::endl;
        std::cout << rendering(loc_prompt, params);

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
