void World::gen(){
    grid = {};
    //tmpcell.floor.push_back(Floor("roomfloor"));
    initializeMap();
    //create_rooms(25);
    ///////////////////////////////////////////////////////////////
    for(int iy=0; iy<height; iy++){
        for(int ix=0; ix<width; ix++){
            grid[iy][ix].floor.push_back(Floor("roomfloor"));
        }
    }

    //entity[entityCounter] = Entity("player");
    grid[3][4].creatures.push_back(entityCounter);
    entityCounter++;
    ///////////////////////////////////////////////////////////////
}
