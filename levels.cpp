#include "struct.hpp"
#include "main.hpp"
#include <iostream>
using namespace std;

void search_and_build(const tile_data * tiledata){
    cout << "SECTOR: "  << sector_s << endl;

    // init vairables
    bool exists = false;
    int i = 0;

    // search
    for ( ; i < 10; i++){
        if (tiledata[i].x == sector_y && tiledata[i].y == sector_x){
            exists = true;
            cout << " FOUND W DESC: " << tiledata[i].data  << " I: " << i << endl;
            break;
        }
    }
    cout << "EXISTS " << ((exists) ? 1 : 0) << endl;

    // create entities
    if (exists){
        cout << "EXISTS!! NUM: " << tiledata[i].num_level_data << " I:" << i << endl;
        for(int j = 0; j < tiledata[i].num_level_data; j++){
            cout << "LOOKING AT J:" << j << endl;
            switch(tiledata[i].flight_data[j].type){
                case 0: // station
                    cout << "SPAWN STATION AT X:" << tiledata[i].flight_data[j].x;
                    cout << " Y: " << tiledata[i].flight_data[j].y << endl;

                    break;
                case 1: //asteroid
                    cout << "SPAWN ASTEROID AT X:" << tiledata[i].flight_data[j].x;
                    cout << " Y: " << tiledata[i].flight_data[j].y << endl;
                    break;
                case 2: // enemy
                    cout << "SPAWN ENEMY AT X:" << tiledata[i].flight_data[j].x;
                    cout << " Y: " << tiledata[i].flight_data[j].y << endl;
                    break;
                case 3: // debris
                    cout << "SPAWN DEBRIS AT X:" << tiledata[i].flight_data[j].x;
                    cout << " Y: " << tiledata[i].flight_data[j].y << endl;
                    break;
                default:
                    cout << "FAILED WITH: " << tiledata[i].flight_data[j].type << endl;
            }
        }
    } else {
        cout << "SPAWNING NOTHING" << endl;
    }
}
