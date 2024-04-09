#include <string>
#include "../funcs/json.hpp"
using json = nlohmann::json;

class Entity {
public:
    std::string type;
    int hp, hp_max;
    int dmg;
    int y, x; // pos

    Entity(std::string t, int ny, int nx){
        type = t;
        hp = jstats[type]["hp"]; hp_max = jstats[type]["hp"];
        y = ny; x = nx;
        dmg = jstats[type]["dmg"];
    }

    void hit(int n){
        hp -= 1;
    }
};
