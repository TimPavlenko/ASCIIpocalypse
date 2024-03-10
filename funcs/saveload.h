// saveload.h
// ������������ � �������������� map � ������ ������� csv

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <filesystem>
namespace fs = std::filesystem;
//#include "tims_header.h"

void save_map(std::string path, std::map<std::string, std::string> data) {
    if (fs::exists(path)) {
        std::ofstream rewrite(path);
        rewrite.write("", 0);
        rewrite.close();
    }
    std::ofstream f(path, std::ios::app);
    if (f.is_open()) {
        for (auto const& [key, val] : data) {
            f << key << ";" << val << "\n";
        }
        f.close();
    }
}

std::map<std::string, std::string> load_map(std::string path) {
    if (fs::exists(path)) {
        std::ifstream f(path);
        std::map<std::string, std::string> data;
        std::string tmp;
        while (std::getline(f, tmp)) {
            std::vector<std::string> stmp = split(tmp, ';');
            data[stmp[0]] = stmp[1];
        }
        return data;
    }
}
