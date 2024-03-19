#pragma once
#include <string>
#include <vector>
#include "Cell.h"

class World {
public:
	std::string name; // имя для сейва

	std::vector<std::vector<Cell>> grid; // y, x

	void tick(){
		for(int iy=0; iy<grid.size(); iy++){
			for(int ix=0; ix<grid[iy].size(); ix++){
				for(auto cr : grid[iy][ix].creatures){ cr.tick(this); }
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

	void gen(){
		int sizex=10, sizey=9;

		// заполнение сетки пустыми клетками
		grid = {};
		for(int iy=0; iy<sizey; iy++){
			grid.push_back({});
			for(int ix=0; ix<sizex; ix++){
				Cell tmpcell = Cell();
				//tmpcell.floor.push_back(Floor("roomfloor"));
				grid[iy].push_back(tmpcell);
			}
		}
		// наполнение клеток
		
	}

};
