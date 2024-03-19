class World;

class Floor{
public:
    std::string kind;
    void tick(World *world_ptr);
    std::string get_symbol();


    int passable; // 0-непроходимо 1-проходимо 2-только перелететь

    Floor(std::string nkind){
        kind = nkind;
    }

};
