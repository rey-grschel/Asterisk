#include "main.hpp"
#include "levels.hpp"
#include <iostream>
using namespace std;

// texture definitions
sf::Texture character_t;
sf::Texture character_l;
sf::Texture character_b;
sf::Texture character_r;
sf::Texture enemy_t;
sf::Texture enemy_l;
sf::Texture enemy_b;
sf::Texture enemy_r;
sf::Texture asteriod_1;
sf::Texture asteriod_2;
sf::Texture asteriod_3;
sf::Texture debug;
sf::Texture wall;
sf::Texture rockets_tex;
sf::Texture station;
sf::Texture ice_station;
sf::Texture logo;
sf::Texture empty_sector;
sf::Texture ice_field;
sf::Texture nebula;
sf::Texture system_texture;

int g_state = 0;

int init_displays(void){
	for (int i = 0; i < S_HEIGHT * S_WIDTH; i++){
		screen[i] = 32;
	}

	for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            mapdata[i][j] = 0;
        }
	}

    if(!character_t.loadFromFile("res/character-top.png")) return -1;
    if(!character_b.loadFromFile("res/character-bottom.png")) return -1;
    if(!character_r.loadFromFile("res/character-right.png")) return -1;
    if(!character_l.loadFromFile("res/character-left.png")) return -1;
    if(!enemy_t.loadFromFile("res/enemy-top.png")) return -1;
    if(!enemy_r.loadFromFile("res/enemy-right.png")) return -1;
    if(!enemy_b.loadFromFile("res/enemy-bottom.png")) return -1;
    if(!enemy_l.loadFromFile("res/enemy-left.png")) return -1;
    if(!asteriod_1.loadFromFile("res/asteriod-1.png")) return -1;
    if(!asteriod_2.loadFromFile("res/asteriod-2.png")) return -1;
    if(!asteriod_3.loadFromFile("res/asteriod-3.png")) return -1;
    if(!debug.loadFromFile("res/debug.png")) return -1;
    if(!wall.loadFromFile("res/wall.png")) return -1;
    if(!rockets_tex.loadFromFile("res/rockets-2.png")) return -1;
    if(!station.loadFromFile("res/station.png")) return -1;
    if(!ice_station.loadFromFile("res/ice-station.png")) return -1;
    if(!logo.loadFromFile("res/logo.png")) return -1;
    if(!empty_sector.loadFromFile("res/empty_sector.png")) return -1;
    if(!nebula.loadFromFile("res/ice-field.png")) return -1;
    if(!ice_field.loadFromFile("res/nebula.png")) return -1;
    if(!system_texture.loadFromFile("res/system.png")) return -1;

    return 0;
}

int get_terrain(int x, int y){
    return mapdata[(y % HEIGHT)][(x % WIDTH)];
}

void set_terrain(int x, int y, int t){
    mapdata[(y % HEIGHT)][(x % WIDTH)] = t;
}

void cleardisplay(bool _debug){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    if (_debug){
        r.setTexture(&debug);
    } else {
        r.setTexture(&wall);
    }
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j <  HEIGHT; j++){
            r.setPosition(i * 16, j * 16);
            windowTexture.draw(r);
        }
    }
}

void draw_prewarp(int x, int y, int s){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    r.setTexture(&empty_sector);
    for (int i = 1; i < 11; i++){
        for (int j = 1; j < 11; j++){
            switch(level_0_0[i - 1][j - 1]){
                case 0: r.setTexture(&empty_sector); break;
                case 1: r.setTexture(&station); break;
                case 2: r.setTexture(&ice_field); break;
                case 3: r.setTexture(&nebula); break;
                case 4: r.setTexture(&system_texture); break;
            }
            r.setPosition((i * 16) , j * 16);
            windowTexture.draw(r);
            switch(level_0_1[i - 1][j - 1]){
                case 0: r.setTexture(&empty_sector); break;
                case 1: r.setTexture(&station); break;
                case 2: r.setTexture(&ice_field); break;
                case 3: r.setTexture(&nebula); break;
                case 4: r.setTexture(&system_texture); break;
            }
            r.setPosition((i + 11) * 16 , j * 16);
            windowTexture.draw(r);
            switch(level_0_3[i - 1][j - 1]){
                case 0: r.setTexture(&empty_sector); break;
                case 1: r.setTexture(&station); break;
                case 2: r.setTexture(&ice_field); break;
                case 3: r.setTexture(&nebula); break;
                case 4: r.setTexture(&system_texture); break;
            }
            r.setPosition(i * 16 , (j + 11) * 16);
            windowTexture.draw(r);
            switch(level_0_2[i - 1][j - 1]){
                case 0: r.setTexture(&empty_sector); break;
                case 1: r.setTexture(&station); break;
                case 2: r.setTexture(&ice_field); break;
                case 3: r.setTexture(&nebula); break;
                case 4: r.setTexture(&system_texture); break;
            }
            r.setPosition((i + 11) * 16 , (j + 11) * 16);
            windowTexture.draw(r);
        }
    }

    // draw jump position
    if (s == 0) {
        r.setPosition((x + 1) * 16, (y + 1) * 16);
    } else if (s == 1){
        r.setPosition((x + 1) * 16 + 176, (y + 1) * 16);
    } else if (s == 2){
        r.setPosition((x + 1) * 16 + 176, (y + 1) * 16 + 176);
    } else if (s == 3){
        r.setPosition((x + 1) * 16, (y + 1) * 16 + 176);
    }
    r.setTexture(&character_t);
    windowTexture.draw(r);

    // search, inform
    char temp_data[16];
    for (int i = 0; i < 16; i++){
        temp_data[i] = 0;
    }

    switch(s){
        case 0:
            // search
            for (int i = 0; i < 10; i++){
                // yes these need to be switched eventually someone (not me) will fix this
                if(level_0_0_tile_data[i].y == x && level_0_0_tile_data[i].x == y){
                    for (int j = 0; j < 16; j++){
                        temp_data[j] = level_0_0_tile_data[i].data[j];
                    }
                }
            }
            break;
        case 1:
            // search
            for (int i = 0; i < 10; i++){
                // yes these need to be switched eventually someone (not me) will fix this
                if(level_0_1_tile_data[i].y == x && level_0_1_tile_data[i].x == y){
                    for (int j = 0; j < 16; j++){
                        temp_data[j] = level_0_1_tile_data[i].data[j];
                    }
                }
            }
            break;
        case 3:
            // search
            for (int i = 0; i < 10; i++){
                // yes these need to be switched eventually someone (not me) will fix this
                if(level_0_3_tile_data[i].y == x && level_0_3_tile_data[i].x == y){
                    for (int j = 0; j < 16; j++){
                        temp_data[j] = level_0_3_tile_data[i].data[j];
                    }
                }
            }
            break;
        case 2:
            // search
            for (int i = 0; i < 10; i++){
                // yes these need to be switched eventually someone (not me) will fix this
                if(level_0_2_tile_data[i].y == x && level_0_2_tile_data[i].x == y){
                    for (int j = 0; j < 16; j++){
                        temp_data[j] = level_0_2_tile_data[i].data[j];
                    }
                }
            }
            break;
    }
    text.setString(temp_data);
    text.setPosition(368, 112);
    windowTexture.draw(text);


    // draw cuttent position
    if (sector_s == 0) {
        r.setPosition((sector_x + 1) * 16, (sector_y+ 1) * 16);
    } else if (sector_s == 1){
        r.setPosition((sector_x + 1) * 16 + 176, (sector_y + 1) * 16);
    } else if (sector_s == 2){
        r.setPosition((sector_x + 1) * 16 + 176, (sector_y + 1) * 16 + 176);
    } else if (sector_s == 3){
        r.setPosition((sector_x + 1) * 16, (sector_y + 1) * 16 + 176);
    }
    r.setTexture(&enemy_t);
    windowTexture.draw(r);

    text.setString("Warp Config System v12.81.20392");
    text.setPosition(368, 16);
    windowTexture.draw(text);

    text.setString("Quadrant: Epsilon");
    text.setPosition(368, 48);
    windowTexture.draw(text);

    sprintf(tim, "Jump Sector: %d - %d - %d    Current Sector: %d - %d - %d", s, x, y, sector_s, sector_x, sector_y);
    text.setString(tim);
    text.setPosition(368, 64);
    windowTexture.draw(text);

    text.setString("Warp Engine Integrity: 87%");
    text.setPosition(368, 80);
    windowTexture.draw(text);

    text.setString("Use WASD to move jump to coords");
    text.setPosition(368, 320);
    windowTexture.draw(text);

    text.setString("Press ~ to confirm jump");
    text.setPosition(368, 336);
    windowTexture.draw(text);

    windowTexture.display();
}

void draw_self(){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    cleardisplay(false);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(PAD_LEFT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, S_HEIGHT - PAD_BOTTOM)),
        sf::Vertex(sf::Vector2f(PAD_LEFT, S_HEIGHT - PAD_BOTTOM))
    };
    windowTexture.draw(line, 4, sf::Lines);

    text.setString("Your starcruiser: ");
    text.setPosition(PAD_LEFT, PAD_TOP);
    windowTexture.draw(text);

    sprintf(tim, "Health: %d / 500", health);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 16, PAD_TOP + 32);
    windowTexture.draw(text);

    sprintf(tim, "Experience: %d / 5000", experience);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 16, PAD_TOP + 64);
    windowTexture.draw(text);

    sprintf(tim, "Remaining fuel: %d / 10000", fuel);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 16, PAD_TOP + 96);
    windowTexture.draw(text);

    sprintf(tim, "Rockets: %d / 50", rockets);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 16, PAD_TOP + 128);
    windowTexture.draw(text);

    sprintf(tim, "Rounds: %d / 50000", rounds);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 16, PAD_TOP + 160);
    windowTexture.draw(text);

    sprintf(tim, "Credits: %d", credits);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 16, PAD_TOP + 196);
    windowTexture.draw(text);

    windowTexture.display();
}

void draw_menu(int type){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    cleardisplay(false);

    r.setPosition(S_WIDTH - PAD_RIGHT - 32, PAD_TOP + 16);
    r.setTexture(&station);
    windowTexture.draw(r);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(PAD_LEFT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, S_HEIGHT - PAD_BOTTOM)),
        sf::Vertex(sf::Vector2f(PAD_LEFT, S_HEIGHT - PAD_BOTTOM))
    };
    windowTexture.draw(line, 4, sf::Lines);

    text.setString("Viewing: Station 195-2-B");
    text.setPosition(PAD_LEFT, PAD_TOP);
    windowTexture.draw(text);

    text.setString("  Size: 127 Crew, 143 Persons");
    text.setPosition(PAD_LEFT, PAD_TOP + 32);
    windowTexture.draw(text);

    text.setString("  Weight: 12000 metric tons");
    text.setPosition(PAD_LEFT, PAD_TOP + 64);
    windowTexture.draw(text);

    text.setString("  -- Neutral Station --");
    text.setPosition(PAD_LEFT, PAD_TOP + 96);
    windowTexture.draw(text);
}

void display(bool update, int state){
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    cleardisplay(true);

    // rectangle template
    sf::RectangleShape r(sf::Vector2f(16, 16));

    // draw character
    r.setPosition(character_x * 16, character_y * 16);
    switch(facing % 4){
        case 0: r.setTexture(&character_t); break;
        case 1: r.setTexture(&character_r); break;
        case 2: r.setTexture(&character_b); break;
        case 3: r.setTexture(&character_l); break;
        default: r.setTexture(&character_t);
    }
    windowTexture.draw(r);

    // draw enemies
    text.setColor(sf::Color::Red);
    for (int i = 0; i < ENEMIES; i++){
        switch(enemies[i].facing){
            case 0: r.setTexture(&enemy_t); break;
            case 1: r.setTexture(&enemy_r); break;
            case 2: r.setTexture(&enemy_b); break;
            case 3: r.setTexture(&enemy_l); break;
            default: r.setTexture(&debug);
        }
        // windowTexture.draw(r);
        sprintf(tim, "%d", enemies[i].id );
        text.setString(tim);
        text.setPosition(enemies[i].x * 16 + 2, enemies[i].y * 16 -2);
        windowTexture.draw(text);
    }
    text.setColor(sf::Color::White);

    // draw macro entities
    for(int i = 0; i < top_of_entities; i++){
        if(macro_entities[i].type == 0){
            r.setPosition(macro_entities[i].x * 16, macro_entities[i].y * 16);
            r.setTexture(&rockets_tex);
            windowTexture.draw(r);
        } else if (macro_entities[i].type == 1){

        }
    }

    // draw asteroids
    for (int i = 0; i < top_of_asteroids; i++){
        if (asteroids[i].type) {
            r.setTexture(&ice_station);
        } else {
            r.setTexture(&asteriod_2);
        }
        r.setPosition(asteroids[i].x * 16, asteroids[i].y * 16);
        windowTexture.draw(r);
        r.setTexture(&asteriod_1);
        switch(asteroids[i].tiles){
            case 1:
                //set_terrain(x + 1, y, 2);
                r.setPosition((asteroids[i].x + 1) * 16, asteroids[i].y * 16);
                windowTexture.draw(r);
                break;
            case 2:
                //set_terrain(x, y + 1, 2);
                r.setPosition(asteroids[i].x * 16, (asteroids[i].y + 1) * 16);
                windowTexture.draw(r);
                break;
            case 3:
                r.setPosition((asteroids[i].x + 1) * 16, (asteroids[i].y + 1) * 16);
                windowTexture.draw(r);
                break;
            case 4:
                r.setPosition((asteroids[i].x + 1) * 16, asteroids[i].y * 16);
                windowTexture.draw(r);
                r.setPosition((asteroids[i].x + 1) * 16, (asteroids[i].y + 1) * 16);
                windowTexture.draw(r);
                break;
            case 5:
                r.setPosition((asteroids[i].x + 1) * 16, asteroids[i].y * 16);
                windowTexture.draw(r);
                r.setPosition((asteroids[i].x + 1) * 16, (asteroids[i].y + 1) * 16);
                windowTexture.draw(r);
                r.setPosition(asteroids[i].x * 16, (asteroids[i].y + 1) * 16);
                windowTexture.draw(r);
                break;
            default:
                break;
        }
    }

    sprintf(tim, "Health: %d / 500", health);
    text.setString(tim);
    text.setPosition(816, 16);
    windowTexture.draw(text);

    sprintf(tim, "Experience: %d / 5000", experience);
    text.setString(tim);
    text.setPosition(816, 32);
    windowTexture.draw(text);

    sprintf(tim, "Remaining fuel: %d / 10000", fuel);
    text.setString(tim);
    text.setPosition(816, 48);
    windowTexture.draw(text);

    sprintf(tim, "At: s%d (%d , %d)", sector_s, sector_x, sector_y);
    text.setString(tim);
    text.setPosition(816, 64);
    windowTexture.draw(text);

    windowTexture.display();


}

void draw_logo(){
    sf::RectangleShape r(sf::Vector2f(S_WIDTH, S_HEIGHT));
    r.setTexture(&logo);
    windowTexture.draw(r);
    windowTexture.display();
}
