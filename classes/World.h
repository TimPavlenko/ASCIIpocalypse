#pragma once
#include <string>
#include <vector>
#include "../funcs/platform.h"
#include "../tims_header.h"
#include "Entity.cpp"
//#include "json.hpp"
//using json = nlohmann::json;

class World {
public:
	// Наполнение мира:
	std::string name; // имя для сейва
	std::string location_name;
	int tick_counter = 0, lvl_counter = 1;
	std::vector<Entity> entity;


	// Окружение:
	int height, width;

	// (y, x):
	std::vector<std::vector<std::string>> floor;
	std::vector<std::vector<std::string>> items;
	std::vector<std::vector<std::string>> creatures;

	void tick(){
		jornal.push_back(std::to_string(entity.size()));

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
		int players_dmg{0};
		// Логика игрока (он ходит первым)
		for(int i=0; i<entity.size(); i++){
			if (entity[i].type == "player"){
				players_dmg = entity[i].dmg;

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
				// Взаимодействие при попытке "пойти в объект":
				if(!stay){
					//std::cout << symbol_is(creatures[del_y][del_x]);
					//wait_key_press();
					if ( creatures[del_y][del_x]!="@" &&
					symbol_in(creatures[del_y][del_x])=="creature"/* &&
					creatures[del_y][del_x]!="@" &&
					floor[del_y][del_x]!=">"*/) {
						//jornal.push_back(creatures[del_y][del_x]);
						stay = true;
						for(int i=0; i<entity.size(); i++){
							if(entity[i].y == del_y && entity[i].x == del_x){
								jornal.push_back(std::to_string(tick_counter)+"> "+entity[i].type+" hited to "+std::to_string(players_dmg)+" dmg");
								entity[i].hit(players_dmg);
								if(entity[i].hp <= 0){ jornal.push_back(std::to_string(tick_counter)+"> "+"ant dead"); }
							}
						}
					} else if (floor[del_y][del_x]==">") {
						lvl_counter++;
						tick_counter++;
						gen(lvl_counter);
						return;
					}
				}
				// Движение:
				if(stay==false){
					tmpv[del_y][del_x] = "@";
					creatures[entity[i].y][entity[i].x]=" ";
					entity[i].y=del_y; entity[i].x=del_x;
				}else{
					tmpv[entity[i].y][entity[i].x] = "@";
				}
			}
		}

		// Проверка смерти у монстров
		for(int i=0; i<entity.size(); i++){
			if(entity[i].hp<=0){
				entity.erase(entity.begin() + i);
				jornal.push_back(symbol_in("a"));
			}
		}

		// Логика монстров (ходят после игрока, если пережили его ход)
		for(int i=0; i<entity.size(); i++){
			if (entity[i].type != "@"){
				creatures[entity[i].y][entity[i].x]=" ";
				tmpv[entity[i].y][entity[i].x] = chmap_creature[entity[i].type];
			}
		}

		// Обновление данных для UI:
		for(int i=0; i<entity.size(); i++){
			if (entity[i].type == "player"){
				cross_screen_buffer["player_hp"] = entity[i].hp;
				cross_screen_buffer["player_hp_max"] = entity[i].hp_max;
			}
		}

		creatures = tmpv;
		tick_counter++;
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

	void gen(int n){

		cross_screen_buffer["pl_y"] = 4;
		cross_screen_buffer["pl_x"] = 3;
		switch (n) {
			case 1: // пещеры (1-1)
				location_name = "1-1";
				// сюда стоит добавить мысли персонажа, разные (как сплэши из майна) в разных забегах
				jornal.push_back(std::to_string(tick_counter)+"> Descent to: 1-1 (caves)");
				jornal.push_back(std::to_string(tick_counter)+"> You enter the Caves. The evil oozing from the lower floors has reached here.");

				cross_screen_buffer["pl_y"] = 4;
				cross_screen_buffer["pl_x"] = 3;
			break;
			case 2: // пещеры (1-2)
				location_name = "1-2";
				jornal.push_back(std::to_string(tick_counter)+"> Descent to: 1-2 (caves)");
				jornal.push_back(std::to_string(tick_counter)+"> It got colder. Light from the surface no longer penetrates here.");
			break;
			case 3: // пещеры (1-2)
				location_name = "1-3";
				jornal.push_back(std::to_string(tick_counter)+"> Descent to: 1-3 (caves)");
				jornal.push_back(std::to_string(tick_counter)+"> The echo brings to you the sounds of swarming local inhabitants");
			break;
			default:
				location_name = "?-"+std::to_string(n);
			break;
		}

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
		// ПОЧЕМУ ТО ИНОГДА УМИРАЕТ НА ЭТАПЕ РАССТАНОВКИ ГОЛДЫ
		/*int gold_num_to_gen = 2;
		for(int i=0; i<gold_num_to_gen; i++){
			for(int ii=0; ii<100; ii++){
				int ny=rfr(0, height), nx=rfr(0, width);
				if(floor[ny][nx]==chmap_floor["roomfloor"]){
					items[ny][nx] = "$";
					std::cout << "$"<< std::endl;
					ii=100;
				}
			}
		}*/


		// Существа
		creatures = {};
		entity = {};
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

		Entity new_player_ent = Entity("player", cross_screen_buffer["pl_y"], cross_screen_buffer["pl_x"]);
		creatures[new_player_ent.y][new_player_ent.x] = chmap_creature["player"];
		cross_screen_buffer["player_hp"] = new_player_ent.hp;
		cross_screen_buffer["player_hp_max"] = new_player_ent.hp;
		entity.push_back(new_player_ent);

		Entity new_enemy_ent1 = Entity("ant", 1, 1);
		creatures[new_enemy_ent1.y][new_enemy_ent1.x] = chmap_creature["ant"];
		entity.push_back(new_enemy_ent1);

		Entity new_enemy_ent2 = Entity("ant", 4, 16);
		creatures[new_enemy_ent2.y][new_enemy_ent2.x] = chmap_creature["ant"];
		entity.push_back(new_enemy_ent2);

	}

};
