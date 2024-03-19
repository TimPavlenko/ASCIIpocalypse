class World;

class Entity{
public:
    std::string kind;
    void tick(World *world_ptr);
    std::string get_symbol();
};
