std::string Cell::get_ch(){
    std::string rez = " ";
    if(!floor.empty()){ rez=floor[floor.size()-1].get_symbol(); }
    if(!objects.empty()){ rez=objects[objects.size()-1].get_symbol(); }
    //if(!creatures.empty()){ rez=creatures[creatures.size()-1].get_symbol(); }
    if(!creatures.empty()){
        cur_world.entity[creatures[creatures.size()-1]].get_symbol();
    }

    return rez;
}
