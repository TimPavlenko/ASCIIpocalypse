#pragma once
class World;

class Object{
public:
    std::string kind;
    void tick(World *world_ptr);
    std::string get_symbol();

    Object(std::string nkind);
};
