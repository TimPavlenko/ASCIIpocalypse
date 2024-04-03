#pragma once

#include "Object.h"

#include "Floor.h"

class World;

class Cell {
public:
    std::vector<unsigned long> creatures = {};
    std::vector<Object> objects = {};
    std::vector<Floor> floor = {};

    std::string get_ch();
};
