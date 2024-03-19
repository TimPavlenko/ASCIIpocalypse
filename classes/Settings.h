#pragma once
#include <string>
#include <vector>
#include "../funcs/json.hpp"
using json = nlohmann::json;

class Settings {
public:
	int w;
    int h;
    //bool flscrn;
	bool reverse_jornal;

	Settings() {
		w = 100;
		h = 20;
		reverse_jornal = false;
	}

	void serialize(std::string path){
		json jsonfile;

		jsonfile["w"] = w;
		jsonfile["h"] = h;
		jsonfile["reverse_jornal"] = reverse_jornal;

		std::ofstream file(path);
		file << jsonfile;
	}

	void deserialize(std::string path){
		std::ifstream ifs(path);
		json jf = json::parse(ifs);

		w = jf["w"];
		h = jf["h"];
		reverse_jornal = jf["reverse_jornal"];
	}

};
