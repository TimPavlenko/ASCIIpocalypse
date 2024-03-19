#pragma once

#include "Object.h"
#include "Entity.h"
#include "Floor.h"

class World;

class Cell {
public:
    std::vector<Entity> creatures;
    std::vector<Object> objects;
    std::vector<Floor> floor;

    std::string get_ch(){
        std::string rez = "";
        if(!floor.empty()){ rez=floor[floor.size()-1].get_symbol(); }
        //if(!objects.empty()){ rez=objects[objects.size()-1].get_symbol() }
        //if(!creatures.empty()){ rez=creatures[creatures.size()-1].get_symbol() }
        return rez;
    }
};
