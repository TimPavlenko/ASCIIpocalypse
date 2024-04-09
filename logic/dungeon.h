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
                        "size": [ 50, 1 ],
                        "children": []
                    },
                    "status_lbl_2": {
                        "text": "s2_text",

                        "type": "label",
                        "pos": [ 1, "2s_lbl_posy" ],
                        "size": [ 50, 1 ],
                        "children": []
                    }
                }
            ]
        }
    })END";

    bool run = true;
    while (run) {
        // Формирование play_against_greed:
        //std::string pa_greed_cells = "   - - - - -;   | @ . . |;   | . . . | ;   | . . . + # # #   - - - - -;   - - - - -     #   | . . . |;                 # # + . . . |;                 #   - - - - -;             - - + - - - ; - - - - -   | . . . . |; | . . . + # # . . . [ |; | > . . |   | . g . . |; - - - - -   | . . . . |;       	     - - - - - -";
        std::string pa_greed_cells = cur_world.get_str();

        // формирование журнала:
        std::string jornal_text = "";
        std::string log_sep = "| ";
        std::vector<std::string> jornal_v_tmp = {};
        for(int i=0; i<settings.h; i++){
            if(i+1>jornal.size()){
                jornal_v_tmp.push_back(" ");
            }else{
                //jornal_v_tmp.push_back(jornal[i]);
                /*if(jornal[i].size()>vsep1_indent){
                    jornal_v_tmp.insert(jornal_v_tmp.begin(), "long stroka ;}");
                }else{*/
                    int nn = 0;
                    if(jornal.size()>settings.h){
                        nn = jornal.size()-settings.h;
                    }

                    jornal_v_tmp.insert(jornal_v_tmp.begin(), jornal[i+nn]);
                //}
            }
        }
        if(settings.reverse_jornal){ std::reverse( jornal_v_tmp.begin(), jornal_v_tmp.end() ); }
        for(int i=0; i<jornal_v_tmp.size(); i++){
            jornal_text+=jornal_v_tmp[i];
            if(i<jornal_v_tmp.size()-1){ jornal_text+=";"; }
        }
        // Перенос длинных строк
        auto trimming_long_lines {
			[&](std::string jt){
                std::vector<std::string> words;
                std::istringstream iss(jt);
                std::string word;
                int num_deleted = 0;
                while (getline(iss, word, ';')) {
                    if (word.length() > vsep1_indent-log_sep.size()) {
                        int start = 0;
                        while (start < word.length()) {
                            words.push_back(word.substr(start, vsep1_indent-log_sep.size()));
                            start += vsep1_indent-log_sep.size();

                        }
                        num_deleted++;

                    } else {
                        words.push_back(word);
                    }
                }
                if(!settings.reverse_jornal){
                    for (int i = 0; i < num_deleted; ++i) {
                        words.pop_back();
                    }
                }else{
                    words.erase(words.begin(), words.begin() + num_deleted);
                }

                return words;
            }
		};

        jornal_v_tmp = trimming_long_lines(jornal_text);
        jornal_text = "";
        //std::cout << jornal_v_tmp.size() << std::endl;
        for(int i=0; i<jornal_v_tmp.size(); i++){
            jornal_text+=log_sep+jornal_v_tmp[i];
            if(i<jornal_v_tmp.size()-1){ jornal_text+=";"; }
        }

        // Статусбар:
        std::string sep_buff = "";
        for(int i=0; i<settings.w-vsep1_indent; i++){ sep_buff+="_"; }

        std::string hp_status = cat( std::to_string(cross_screen_buffer["player_hp"]), "/", std::to_string(cross_screen_buffer["player_hp_max"]));
        std::string status_line_1 = "HP: "+rem(7, hp_status)+" AC: 10  "+" loc: "+cur_world.location_name;
        //std::string status_line_2 = std::format("XP: [{}] $: 45   T: [{}]"   , rem(7, "20/100"), rem(5, std::to_string(cur_world.tick_counter)));
        std::string status_line_2 = "XP: "+rem(7, "46/50")+" $: 45   "+" T: "+std::to_string(cur_world.tick_counter);//"T: 27   ";


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
                cur_world.tick();
            break;
            case ARROW_DOWN:
                cross_screen_buffer["PlayerCom"] = 2;
                cur_world.tick();
            break;
            case ARROW_LEFT:
                cross_screen_buffer["PlayerCom"] = 3;
                cur_world.tick();
            break;
            case ARROW_RIGHT:
                cross_screen_buffer["PlayerCom"] = 4;
                cur_world.tick();
            break;
        }

        // победа ?
        if(cur_world.lvl_counter > end_lvl_num){
            cur_menu_num = END;
            run = false;
        }

    }
}
