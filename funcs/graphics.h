// graphics.h
// ф-ии отрисовки

#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "json.hpp"
using json = nlohmann::json;

std::vector<std::vector<std::string>> rez = {};

void traversal(auto j, std::string type) {
	//std::cout << "key:" << it.key() << std::endl;
	std::vector<std::vector<std::string>> prerez = {};
	int size_x = j["size"][0];
	int size_y = j["size"][1];
	int pos_x = j["pos"][0];
	int pos_y = j["pos"][1];

	// Общие действия
	std::vector<std::string> line = {};
	for(int x=0; x<size_x; x++){
		line.push_back(" ");
	}
	for(int y=0; y<size_y; y++){
		prerez.push_back(line);
	}
	line = {};


	// Специфичные действия разных типов
	if (type == "label") { // лейбл пока не поддерживает мультистроку (деление на строки по разделителям)
		std::vector<std::string> line = {};
		int lbl_text_size = size_x;
		std::string str = j["text"];

		const char* ch_arr = str.c_str();
		for (int i = 0; i < str.size(); i++) {
			line.push_back(std::string{ ch_arr[i] });
		}

		//int free_space = lbl_text_size - div_up(std::string{ j["text"] }.size(), 2);
		//line.push_back(std::string{ j["text"] });
		for (int i = 0; i < lbl_text_size-str.size(); i++) {
			line.push_back(" ");
		}

		prerez[div_up(size_y, 2)-1] = line;

	}
	if (type == "multiline") {
		std::vector<std::string> strv = split(j["text"], ';');

		int lbl_text_size = size_x;
		int ii = 0;

		for(std::string str : strv) {
			std::vector<std::string> line = {};

			const char* ch_arr = str.c_str();
			for (int i = 0; i < str.size(); i++) {
				line.push_back(std::string{ ch_arr[i] });
			}
			for (int i = 0; i < lbl_text_size-str.size(); i++) {
				line.push_back(" ");
			}

			if(ii<size_y){
				prerez[ii] = line;
			}
			ii++;
		}
	}
	if (type == "panel") {
		prerez = {}; // костыль
		std::vector<std::string> line = {};
		line.push_back("_");
		for (int i = 1; i < size_x - 1; i++) {
			line.push_back("-");
		}
		line.push_back("_");
		prerez.push_back(line);

		for (int i = 1; i < size_y - 1; i++) {
			line = {};
			line.push_back("|");
			for (int j = 1; j < size_x - 1; j++) {
				line.push_back(" ");
			}
			line.push_back("|");
			//prerez[i].push_back(line);
			prerez.push_back(line);
		}

		line = {};
		line.push_back("_");
		for (int i = 1; i < size_x - 1; i++) {
			line.push_back("-");
		}

		line.push_back("_");
		prerez.push_back(line);
	}

	if (type == "grid") {
		std::string str = j["cells"];
		std::vector<std::string> vstr = split(str, ';');
		/*for(auto s : vstr){
			print(s);
		}*/

		int iv=0;
		for(int iy=0; iy<size_y; iy++){
			if(iy <= vstr.size() && iv < vstr.size()){
				std::vector<std::string> locline;

				std::string str = vstr[iv];
				const char* ch_arr = str.c_str();
				for (int i = 0; i < str.size(); i++) {
					locline.push_back(std::string{ ch_arr[i] });
				}
				for (int i = 0; i < size_x-str.size(); i++) {
					locline.push_back(" ");
				}
				prerez[iy] = locline;
				iv++;
			}
		}
	}

	// Позиционирование
	for (int i = 0; i < pos_y; i++) { // сдвиг вниз
		std::vector<std::string> dop_line = {};
		for (int j = 0; j < size_y + pos_y; j++) {
			dop_line.push_back(" ");
		}
		prerez.insert(prerez.begin(), dop_line);
	}
	for (int i = 0; i < pos_x; i++) { // сдвиг вправо
		for (int j = 0; j < prerez.size(); j++) {
			prerez[j].insert(prerez[j].begin(), " ");
		}
	}

	// Дебаг: Вывод слоя без наложения
	/*std::cout << std::endl << "name:" << type << std::endl;
	for (int iy = 0; iy < prerez.size(); iy++) {
		for (int ix = 0; ix < prerez[iy].size(); ix++) {
			std::cout << prerez[iy][ix];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	// Наложение
	for (int iy = 0; iy < prerez.size(); iy++) {
		for (int ix = 0; ix < prerez[iy].size(); ix++) {
			if (prerez[iy][ix] != " ") {
				rez[iy][ix] = prerez[iy][ix];
			}
		}
	}


	// Рекурсия
	for (auto it = j["children"][0].begin(); it != j["children"][0].end(); ++it) {
		//std::cout << it.key() << std::endl;
		traversal(j["children"][0][it.key()], j["children"][0][it.key()]["type"] /*it.key()*/);
	}

}

void set_parameters(json* j_ptr, std::map<std::string, std::string>* parameters_ptr) {
	//(*j_ptr)["parts"] = false;

	for (auto it = (*j_ptr).begin(); it != (*j_ptr).end(); ++it) {
		//std::cout << it.key() << std::endl;

		if ((it.key() == "pos") or (it.key() == "size")) {
			if (it.value()[0].is_string()) {
				if ((*parameters_ptr).find(it.value()[0]) != (*parameters_ptr).end()) {
					(*j_ptr)[it.key()][0] = std::stoi((*parameters_ptr)[it.value()[0]]);
				}
			}
			if (it.value()[1].is_string()) {
				if ((*parameters_ptr).find(it.value()[1]) != (*parameters_ptr).end()) {
					(*j_ptr)[it.key()][1] = std::stoi((*parameters_ptr)[it.value()[1]]);
				}
			}
		}
		if (it.key() == "text" || it.key() == "cells") {
			//if (it.value().is_string()) {
				if ((*parameters_ptr).find(it.value()) != (*parameters_ptr).end()) {
					(*j_ptr)[it.key()] = (*parameters_ptr)[it.value()];
				}
			//}
		}
	}

	for (auto it = (*j_ptr)["children"][0].begin(); it != (*j_ptr)["children"][0].end(); ++it) {
		set_parameters(&(*j_ptr)["children"][0][it.key()], &(*parameters_ptr));
	}

	//(*j_ptr)["children"][0]["label"]["text"] = "kill them all";
}

std::string rendering(auto prompt, std::map<std::string, std::string> parameters) {
	// Парсинг JSON
	/*std::ifstream i("file.json");
	json j;
	i >> j;*/
	json jdata = json::parse(prompt);//,nullptr, true, true); // json с комментами не кушает никак
	/*
	std::cout << jdata["guild"] << std::endl;
	//std::cout << typeid(jdata["guild"]).name() << std::endl;
	std::cout << jdata["guild"].empty() << std::endl;
	std::cout << jdata["guild"]["name"].empty() << std::endl;
	*/

	// Подстановка параметров
	set_parameters(&jdata["root"], &parameters);
	//std::cout << jdata["root"]["children"][0]["label"]["text"] << std::endl;

	rez.clear();
	std::string srez = "";

	// Задание размера root согласно промпту
	for (int i = 0; i<jdata["root"]["size"][1]; i++) {
		std::vector<std::string> line = {};
		for (int i = 0; i < jdata["root"]["size"][0]; i++) {
			line.push_back(" ");
		}
		rez.push_back(line);
	}

	traversal(jdata["root"], "root");

	for (int i = 0; i < rez.size(); i++) {
		std::stringstream buffer;
		for (auto ch : rez[i]) {
			buffer << ch;// << " ";
		}
		if (i < rez.size() - 1) {
			srez += buffer.str() + "\n";
		}
		else {
			srez += buffer.str();
		}
	}
	return srez;
}
