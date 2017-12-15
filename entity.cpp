#include "main.hpp"
#include "display.hpp"
#include <iostream>
using namespace std;

void update_enemies(){
    if (time_enemy > TIME_ENEMY ){
        time_enemy = 0;
        cout << "UD E" << endl;
        for(int i = 0; i < ENEMIES; i++){
            if ( (enemies[i].x > WIDTH || enemies[i].x < 0 || enemies[i].y < 0 || enemies[i].y > HEIGHT ) && enemies[i].id > 0){
                enemies[i].x = -10;
                enemies[i].y = -10;
                enemies[i].facing = -1;
                cout << "ERASED" << endl;
            }
        }
        for(int i = 0; i < ENEMIES; i++){
            switch (enemies[i].facing){
                case 0:
                    enemies[i].y--;
                    break;
                case 1:
                    enemies[i].y++;
                    break;
                case 2:
                    enemies[i].y++;
                    break;
                case 3:
                    enemies[i].x--;
                    break;
                default:
                    break;
            }
        }
    }
}

void update_macro(void){
    if (time_macro > TIME_MACRO){
        time_macro = 0;
        for (int i = 0; i < top_of_entities; i++){
            // remove out of bound entities
            if (macro_entities[i].x > WIDTH || macro_entities[i].x < 0 || macro_entities[i].y > HEIGHT || macro_entities[i].y < 0){
                for (int j = i; j < top_of_entities; j++){
                    macro_entities[j] = macro_entities[j + 1];
                }
                top_of_entities--;
            }

            // update entities
            if (macro_entities[i].type == 0){
                switch(macro_entities[i].facing){
                    case 0: macro_entities[i].y--; break;
                    case 1: macro_entities[i].x++; break;
                    case 2: macro_entities[i].y++; break;
                    case 3: macro_entities[i].x--; break;
                    case 4: macro_entities[i].y--; macro_entities[i].x++; break;
                    case 5: macro_entities[i].x++; macro_entities[i].y++; break;
                    case 6: macro_entities[i].y++; macro_entities[i].x--;break;
                    case 7: macro_entities[i].x--; macro_entities[i].y--;break;
                    default: break;
                }
                for(int k = 0; k < ENEMIES; k++){
                    if (enemies[k].x == macro_entities[i].x && enemies[k].y == macro_entities[i].y){
                        for (int j = i; j < top_of_entities; j++){
                            macro_entities[j] = macro_entities[j + 1];
                        }
                        top_of_entities--;
                    }
                }
            }
        }
    }

    // update character
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

void update_asteroids(void){
    if (time_asteroid > TIME_ASTROID){
        time_asteroid = 9;
        for (int i = 0; i < top_of_asteroids; i++){
            asteroids[i].x += asteroids[i].mod_vx;
            asteroids[i].y += asteroids[i].mod_vy;
        }
    }
}

