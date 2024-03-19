#pragma once
#include <string>
#include <vector>

std::vector<std::vector<std::string>> tunel_alg(int sizex, int sizey){
    // установка размера подземелья
    std::vector<std::vector<std::string>> rez = {};
    for(int iy; iy<sizey; iy++){
        std::vector<std::string> line = {};
        for(int ix; ix<sizex; ix++){
            line.push_back(" ");
        }
        rez.push_back(line);
    }




    return rez;
}
