#pragma once
#include <string>
#include <vector>
#include "../funcs/platform.h"
#include "../tims_header.h"
#include "Entity.cpp"

class World {
public:
	// Наполнение мира:
	std::string name; // имя для сейва
	int tick_counter = 0;
	std::vector<Entity> entity;


	// Окружение:
	int height, width;

	// (y, x):
	std::vector<std::vector<std::string>> floor;
	std::vector<std::vector<std::string>> items;
	std::vector<std::vector<std::string>> creatures;

	void tick(){

		auto can_move_to {
			[&](int y, int x){
				if(floor[y][x]==chmap_floor["roomfloor"] ||
				floor[y][x]==chmap_floor["corridor"] ||
				floor[y][x]==chmap_floor["upstairs"] ||
				floor[y][x]==chmap_floor["downstairs"]){
					return true;
				}else{
					return false;
				}
			}
		};

		std::vector<std::vector<std::string>> tmpv(height, std::vector<std::string>(width, " "));
		for(int i=0; i<entity.size(); i++){
			if (entity[i].type == "player"){
				bool stay = true;
				int del_y=entity[i].y, del_x=entity[i].x;
				switch (cross_screen_buffer["PlayerCom"]) {
					case 1:
						if(can_move_to(entity[i].y-1, entity[i].x)){del_y--; stay=false;}
					break;
					case 2:
						if(can_move_to(entity[i].y+1, entity[i].x)){del_y++; stay=false;}
					break;
					case 3:
						if(can_move_to(entity[i].y, entity[i].x-1)){del_x--; stay=false;}
					break;
					case 4:
						if(can_move_to(entity[i].y, entity[i].x+1)){del_x++; stay=false;}
					break;
				}
				if(!stay){
					tmpv[del_y][del_x] = "@";
					creatures[entity[i].y][entity[i].x]=" ";
					entity[i].y=del_y; entity[i].x=del_x;
				}else{
					tmpv[entity[i].y][entity[i].x] = "@";
				}
			}/*else if (entity[i].type == "goblin"){

			}*/

		}


		creatures = tmpv;
		tick_counter+=1;
	}

	std::string get_str(/*середина камеры*/){

		std::string rez = "";
		for(int iy=0; iy<floor.size(); iy++){
			for(int ix=0; ix<floor[iy].size(); ix++){
				std::string simbol = " ";
				if(creatures[iy][ix]!=" "){
					simbol=creatures[iy][ix];
				}else if(items[iy][ix]!=" "){
					simbol=items[iy][ix];
				}else{
					simbol=floor[iy][ix];
				}

				rez+=simbol;
				//if(ix!=floor[iy].size()-1){ rez+="+"; }
			}
			rez+=";";
		}

		return rez;
	}
	// ###### генерация ######

	void initializeMap() {
		//floor.assign(height, std::vector<std::string>(width, " "));
		//creatures.assign(height, std::vector<std::string>(width, " "));
		std::vector<std::vector<std::string>> tmpv(height, std::vector<std::string>(width, " "));

		floor = tmpv;
		items = tmpv;
		creatures = tmpv;
    }

	/*
	void create_rooms(int roomsnum, Vector2i minSize=Vector2i(3,3), Vector2i maxSize=Vector2i(6, 6)){// количество комнат, минимальный размер, максимальный размер
		std::vector<std::vector<std::string>> proto;
		// Заполняем всё подземелье стенами
    	for (int iy = 0; iy < height; iy++) {
			std::vector<std::string> line = {};
			for(int ix = 0; ix < width; ix++){
				line.push_back("#");
			}
			proto.push_back(line);
    	}

    	// Генерируем комнаты
    	for (int r = 0; r < roomsnum; ++r) {
        	int roomWidth = rfr(3, 6); // Ширина комнаты
        	int roomHeight = rfr(3, 6); // Высота комнаты
        	int x = rfr(1, width - roomWidth - 1); // Случайная координата X
        	int y = rfr(1, height - roomHeight - 1); // Случайная координата Y

        	// Размещаем комнату
        	for (int i = y; i < y + roomHeight; ++i) {
            	for (int j = x; j < x + roomWidth; ++j) {
                	proto[i][j] = ".";
            	}
        	}
    	}

		///////////////////////////////////////////////////////////////
		for(auto i : proto){
			for(auto j : i){
				std::cout << j << " ";
			}
			std::cout << std::endl;
		}
		std::string rar;
		std::cin >> rar;
		///////////////////////////////////////////////////////////////
	}
	*/

	void gen(){
		// КОСТЫЛИ ХАЛТУРА ОВНОКОД, но задача - сдать, а не долго поддерживать
	    initializeMap();


		// Ландшафт
		floor = {};
		std::vector<std::string> test_dungeon_proto = {
			"------              ",
			"|....|    ----------",
			"|.<..|####.........|",
			"|.....#   |........|",
			"|....|    |......>.|",
			"------    ----------"
		};
		for(std::string dline : test_dungeon_proto){
			std::vector<std::string> nline = {};
			for(char ch : dline){
				std::string s{ch};
				nline.push_back(s);
			}
			floor.push_back(nline);
		}


		// Вещички
		//items = {};
		int gold_num_to_gen = 2;
		for(int i=0; i<gold_num_to_gen; i++){
			bool run = true;
			while (run){
				int ny=rfr(0, height), nx=rfr(0, width);
				if(floor[ny][nx]==chmap_floor["roomfloor"]){
					items[ny][nx] = "$";
					run = false;
				}
			}
		}


		// Существа
		creatures = {};
		std::vector<std::string> test_cretures_proto = {
			"                    ",
			"                    ",
			"                    ",
			"                    ",
			"                    ",
			"                    "
		};
		for(std::string dline : test_cretures_proto){
			std::vector<std::string> nline = {};
			for(char ch : dline){
				std::string s{ch};
				nline.push_back(s);
			}
			creatures.push_back(nline);
		}
		Entity new_player_ent = Entity();
		new_player_ent.y = 4;
		new_player_ent.x = 3;
		new_player_ent.type = "player";
		creatures[new_player_ent.y][new_player_ent.x] = chmap_creature["player"];
		entity.push_back(new_player_ent);



	}

};
