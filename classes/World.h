#pragma once
#include <string>
#include <vector>
#include "Cell.h"

class World {
public:
	std::string name; // имя для сейва

	int height, width;
	std::map<unsigned long, Entity> entity; // id, entity
	std::vector<std::vector<Cell>> grid; // y, x

	void tick(){
		for(auto& en : entity){
    		en.second.tick(this);
		}
		for(int iy=0; iy<grid.size(); iy++){
			for(int ix=0; ix<grid[iy].size(); ix++){
				//for(auto cr : grid[iy][ix].creatures){ cr.tick(this); }
				for(auto ob : grid[iy][ix].objects){ ob.tick(this); }
			}
		}
	}

	std::string get_str(/*середина камеры*/){
		std::string rez = "";
		for(int iy=0; iy<grid.size(); iy++){
			for(int ix=0; ix<grid[iy].size(); ix++){
				rez+=grid[iy][ix].get_ch();
				if(ix!=grid[iy].size()-1){ rez+=" "; }
			}
			rez+=";";
		}
		return rez;
	}
	// ###### генерация ######

	void initializeMap() {
        grid.assign(height, std::vector<Cell>(width, Cell()));
    }

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

	void gen();

};
