#include "main.hpp"
#include "terrain.hpp"
#include "display.hpp"
#include <iostream>
using namespace std;

void update_entities(){
    if (time_entity > TIME_ENTITY ){
        time_entity = 0;
        for (int i = 0; i < num_entities; i++){
            if (entities[i].x >= WIDTH - 1 || entities[i].x <= 0) entities[i].vx = - entities[i].vx;
            if (entities[i].y >= HEIGHT - 1 || entities[i].y <= 0) entities[i].vy = - entities[i].vy;
            entities[i].x += entities[i].vx;
            entities[i].y += entities[i].vy;
        }
    }

    if (time_character > TIME_CHARACTER){
        time_character = 0;
        switch(facing){
            case 0: character_y--; break;
            case 1: character_x++; break;
            case 2: character_y++; break;
            case 3: character_x--; break;
            case 4: character_y--; character_x++; break;
            case 5: character_x++; character_y++; break;
            case 6: character_y++; character_x--; break;
            case 7: character_x--; character_y--; break;
            default: break;
        }
    }
}
