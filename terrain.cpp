#include "main.hpp"
#include "display.hpp"
#include <iostream>
using namespace std;

// global enemy list

void generate_asteroid(int x, int y){
    // set origin tile
    set_terrain(x, y, 1);

    // add peripheral tiles
    int tiles = 0;
    switch(rand() % 5){
        case 0:
            set_terrain(x + 1, y, 2);
            tiles = 1;
            break;
        case 1:
            set_terrain(x, y + 1, 2);
            tiles = 2;
            break;
        case 2:
            set_terrain(x + 1, y + 1, 2);
            tiles = 3;
            break;
        case 3:
            set_terrain(x + 1, y, 2);
            set_terrain(x + 1, y + 1, 2);
            tiles = 4;
            break;
        default:
            set_terrain(x + 1, y, 2);
            set_terrain(x + 1, y + 1, 2);
            set_terrain(x, y + 1, 2);
            tiles = 5;
            break;
    }

    bool special = false;

    if (rand() % 100 == 4){
        special = true;
        if(rand() % 10 > 5){
            set_terrain(x + 1, y, 12);
        } else {
            set_terrain(x, y + 1, 12);
        }
    }

    if(top_of_asteroids < 32){
        asteroids[top_of_asteroids].x = x;
        asteroids[top_of_asteroids].y = y;
        asteroids[top_of_asteroids].type = special;
        asteroids[top_of_asteroids].facing = rand() % 4;
        asteroids[top_of_asteroids].mod_vx = ((rand() % 10 > 5) ? ((rand() % 10 > 5) ? -1 : 1) : 0);
        asteroids[top_of_asteroids].mod_vy = ((rand() % 10 > 5) ? ((rand() % 10 > 5) ? -1 : 1) : 0);
        asteroids[top_of_asteroids].tiles = tiles;

        top_of_asteroids++;
    }

}

void generate_level(void){
    for (int i = 0; i < 10; i++){
        int x = rand() % (WIDTH - 10);
        int y = rand() % (HEIGHT - 10);
        generate_asteroid(x, y);
    }

    for (int i = 0; i < ENEMIES; i++){
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        if (!(get_terrain(x,y))) {
           //set_terrain(x, y, -i);
           enemies[i].tile_id = -i;
           enemies[i].id = i;
           enemies[i].x = x;
           enemies[i].y = y;
           enemies[i].facing = (rand() % 3);
           cout << "placed enemy" << endl;
        }
    }

    for(int i = 0; i < 3; i++){
        int xt = rand() % (WIDTH - 1) + 1;
        int yt = rand() % (HEIGHT - 1) + 1;
        if(!get_terrain(xt,yt)){
            set_terrain(xt,yt,12);
        }
    }

    character_x = rand() % 10 + 25;
    character_y = HEIGHT - (rand() % 10 + 25);
    while (get_terrain(character_x, character_y) != 0){
        character_x = rand() % 10 + 25;
        character_y = HEIGHT - (rand() % 10 + 25);
    }
}
