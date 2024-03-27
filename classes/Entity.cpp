Entity::Entity(std::string nkind){
    kind = nkind;
}

void Entity::tick(World *world_ptr){
    print("Entity_tick!");
}

std::string Entity::get_symbol(){
    return chmap_creature[kind];
    if(kind=="player"){
        components.push_back(CompPlayer());
    }
}
