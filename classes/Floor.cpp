void Floor::tick(World *world_ptr){
    print("Floor_tick!");
}

std::string Floor::get_symbol(){
    return chmap_floor[kind];
}
