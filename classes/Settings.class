#pragma once
#include <string>
#include <vector>
#include "../funcs/saveload.h"

class Settings {
public:
	int w;
    int h;
    bool flscrn;
	Settings (std::map<std::string, std::string> m) {
		w = stoi(m["w"]);
		h = stoi(m["h"]);
		flscrn = to_bool(m["flscrn"]);
	}
	Settings () {
		w = 100;
		h = 20;
		flscrn = false;
	}

	void serialize(std::string path){

		auto flscrn_var = [](bool v){ if(v){return "true";}else{return "false";} };

		std::map<std::string, std::string> m = {
			{"w", std::to_string(w)},
			{"h", std::to_string(h)},
			{"flscrn", flscrn_var(flscrn)}
		};
		save_map(path, m);
	}

};
