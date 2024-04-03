#pragma once

void sc_resolution_setting() {

    int last_w = settings.w;
    int last_h = settings.h;
    std::string loc_prompt = R"END({
        "root": {
            "type": "root",
            "pos": [ 0, 0 ],
            "size": [ "rsizex", "rsizey" ],
            "parts": true,
            "children": [
                {
                    "noun_lbl": {
                        "text": "use arrows to edit resolution",

                        "type": "label",
                        "pos": [ 2, 2 ],
                        "size": [ 29, 1 ],
                        "parts": false,
                        "children": []
                    },
                    "noun2_lbl": {
                        "text": "press Enter to finish",

                        "type": "label",
                        "pos": [ 2, 3 ],
                        "size": [ 21, 1 ],
                        "parts": false,
                        "children": []
                    },
                    "min_res_lbl": {
                        "text": "min: 100x20",

                        "type": "label",
                        "pos": [ 2, 5 ],
                        "size": [ 11, 1 ],
                        "parts": false,
                        "children": []
                    },
                    "res_lbl": {
                        "text": "k_res",

                        "type": "label",
                        "pos": [ 2, 6 ],
                        "size": [ 7, 1 ],
                        "parts": false,
                        "children": []
                    }
                }
            ]
        }
    })END";

    bool run = true;
    while (run) {
        clear();
        std::map<std::string, std::string> params = {
            {"rsizex", std::to_string(settings.w) },
            {"rsizey", std::to_string(settings.h) },
            {"k_res", cat(std::to_string(settings.w), "x", std::to_string(settings.h)) }

        };
        std::cout << rendering(loc_prompt, params);

        switch ((int)wait_key_press()) {
            case ARROW_UP:
                if(settings.h>min_h){ settings.h -= 1; }
            break;
            case ARROW_DOWN:
                if(settings.h<max_h){ settings.h += 1; }
            break;
            case ARROW_LEFT:
                if(settings.w>min_w){ settings.w -= 1; }
            break;
            case ARROW_RIGHT:
                if(settings.w<max_w){ settings.w += 1; }
            break;
            case KEY_ENTER:
                run = false;
            break;
        }
        if((settings.w != last_w) || (settings.h != last_h)){
            resize_window(settings.w, settings.h);
            last_w = settings.w;
            last_h = settings.h;
        }
    }
    settings.serialize(settings_path);
}

void sc_options() {
    short arrow_pointer = 3;

    auto arrow_pointer_op{
        [&arrow_pointer](short p){ if(arrow_pointer==p){ return std::string{">"}; }else{ return std::string{" "}; } }
    };

    auto true_cross{
        [](bool p){ if(p){ return "x"; }else{ return " "; } }
    };

    bool run = true;
    while (run) {
        clear();
        std::map<std::string, std::string> params = {
            {"k_a3", cat(arrow_pointer_op(1), std::format("reverse jornal [{}]", true_cross(settings.reverse_jornal))) },
            {"k_a2", cat(arrow_pointer_op(2), "resolution")},
            {"k_a1", cat(arrow_pointer_op(3), "back")},
            {"root_x", std::to_string(settings.w) },
            {"root_y", std::to_string(settings.h) }
        };
        std::cout << rendering(read_file("screens/options.sc"), params);

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
                        if(settings.reverse_jornal){settings.reverse_jornal=false;}else{settings.reverse_jornal=true;}
                    break;
                    case 2:
                        sc_resolution_setting();
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
