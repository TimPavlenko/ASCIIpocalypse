Object::Object(std::string nkind){
    kind = nkind;
}

void Object::tick(World *world_ptr){
    print("World_tick!");
}

std::string Object::get_symbol(){
    return chmap_floor[kind];
}
