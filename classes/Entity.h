class World;
#include "Components.h"

class Entity{
public:
    std::string kind;
    void tick(World *world_ptr);
    std::string get_symbol();

    std::vector<Component> components;
    Entity(std::string nkind);
};
