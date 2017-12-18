#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "main.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "entity.hpp"
#include "levels.hpp"
using namespace std;

// timer
double timerval = 0;
double time_character = 0;
double time_entity = 0;

// enemy defs
entity entities[MAX_ENTITIES];
int num_entities = 0;

// map and screen sizing
int mapdata[HEIGHT][WIDTH];
int screen[S_WIDTH * S_HEIGHT];

// game state: 0 - normal, 1 - ship nav, 2 - combat screen, 3 - character, 4 - port / entity interact
int displaystate = 0;

// character health
int health = 500;

// character experience
float experience = 0;

int rockets = 50;
int rounds = 10000;
int credits = 1000;
int fuel = 10000;

// character location
int character_x = 12;
int character_y = 12;
int dx = 0;
int dy = 0;
int facing = 0;

int sector_s = 3;
int sector_x = 5;
int sector_y = 4;

int level = 0;

// game state
// -1: boot, 0: main map, 1: view, 2: selecting view, 3: view selected, 4: interacting, 5: mod self, 6: mod self confirm, 7: warp setup
int state = -1;

// texture
sf::RenderTexture windowTexture;

int main(){
//    asteriod_direction = 0;

    // set up events
    sf::Event event;

    // initalize rand
    srand (time(NULL));

    cout << "sizeof: " << sizeof(level_0_0_tile_data) << endl;

    // create window
    sf::RenderWindow window(sf::VideoMode(S_WIDTH, S_HEIGHT), "Asterisk");
    sf::RectangleShape rectangle(sf::Vector2f(S_WIDTH, S_HEIGHT));

    // prevent repress
    window.setKeyRepeatEnabled(false);

    // time stuff
    sf::Clock clock;
    sf::Time elapsed;

    // prepare window texture
    if(!windowTexture.create(S_WIDTH, S_HEIGHT)){
        cout << "Failed to build main window texture" << endl;
        return -5;
    }
    //windowTexture.draw(rectangle2);

    // init textures
    if (init_displays() < 0) { return -3; }

    // generate level
    cout << "TERRAIN ..." << endl;
    build_terrain(5, 4, 3);
    cout << "DONE" << endl;

    // generate font
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);

    // init jump position;
    int jump_x = 0;
    int jump_y = 0;
    int jump_s = 0;

    // main loop
    while (window.isOpen()){
        // clean texture
        windowTexture.clear();

        // update timer
        elapsed = clock.restart();
        time_entity += elapsed.asMilliseconds();
        time_character += elapsed.asMilliseconds();

        // handle events
        while (window.pollEvent(event)){
            // close window if needed
            if (event.type == sf::Event::Closed) window.close();

            // check keys (released to avoid repeated keypresses
            if (event.type == sf::Event::KeyReleased) {

                // state handling
                if (event.key.code == sf::Keyboard::Num1) {
                    // main menu
                    state = 0;
                } else if (event.key.code == sf::Keyboard::Num2) {
                    // view ssf::RectangleShape r(sf::Vector2f(16, 16));tate
                    state = 1;
                } else if (event.key.code == sf::Keyboard::Num3) {
                    // view state
                    state = 5;
                } else if (event.key.code == sf::Keyboard::Num4) {
                    // view state
                    state = 7;
                    // reset jump to settings
                    jump_x = sector_x;
                    jump_y = sector_y;
                    jump_s = sector_s;
                } else if (event.key.code == sf::Keyboard::Num0) {
                    // logo mode
                    state = -1;
//                    generate_level();
                }

                // movement handling
                if (event.key.code == sf::Keyboard::W){
                    jump_y--;
                    if (jump_y > 9) jump_y = 9;
                    if (jump_y < 0) jump_y = 0;
                } else if (event.key.code == sf::Keyboard::A){
                    jump_x--;
                    if (jump_x > 9) jump_x = 9;
                    if (jump_x < 0) jump_x = 0;
                } else if (event.key.code == sf::Keyboard::S){
                    jump_y++;
                    if (jump_y > 9) jump_y = 9;
                    if (jump_y < 0) jump_y = 0;
                } else if (event.key.code == sf::Keyboard::D){
                    jump_x++;
                    if (jump_x > 9) jump_x = 9;
                    if (jump_x < 0) jump_x = 0;
                } else if (event.key.code == sf::Keyboard::Q){
                    jump_s++;
                    if (jump_s > 3) jump_s = 0;
                    if (jump_s < 0) jump_s = 3;
                } else if (event.key.code == sf::Keyboard::E) {
                    jump_s--;
                    if (jump_s > 3) jump_s = 0;
                    if (jump_s < 0) jump_s = 3;
                } else if (event.key.code == sf::Keyboard::Tilde && state == 7){
                    sector_x = jump_x;
                    sector_y = jump_y;
                    sector_s = jump_s;// for moving towards the edge of the screen
                    build_terrain(sector_x, sector_y, sector_s);
                    state = 0;
                }

                // navigation handling
                if (event.key.code == sf::Keyboard::BackSpace){
                    facing = -10;
                } else if(event.key.code == sf::Keyboard::Down){
                    if ((get_terrain(character_x, character_y + 1)) == 0){
                        facing = 2;
                    }
                } else if (event.key.code == sf::Keyboard::Up){
                    if ((get_terrain(character_x, character_y - 1)) == 0) {
                        facing = 0;
                    }
                } else if (event.key.code == sf::Keyboard::Left){
                    if ((get_terrain(character_x - 1, character_y)) == 0) {
                        facing = 3;
                    }
                } else if (event.key.code == sf::Keyboard::Right){
                    if ((get_terrain(character_x + 1, character_y)) == 0) {
                        facing = 1;
                    }
                } else if (event.key.code == sf::Keyboard::Space){
                    // TODO: add shooting and state checks
                    state = 0;
                }

                // rotate by 45 deg
                if (event.key.shift){
                    facing += 4;
                } else if (event.key.code == sf::Keyboard::Z){
                    facing -= 4;
                }
            }
        }

        // exit
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            return 0;
        }

        //update everything
        if (state == 0){
            update_entities();
        }

        // draw screen
        switch(state){
            case -1:
                draw_logo();
                break;
            case 0:
            case 2:
                display(0, false);
                break;
            case 1:
                draw_menu(0);
                break;
            case 5:
                draw_self();
                break;
            case 7:
                draw_prewarp(jump_x, jump_y, jump_s);
                break;
            default:
                cleardisplay(false);
                break;
        }

        // display main texture
        windowTexture.setSmooth(true);
        windowTexture.display();
        const sf::Texture& texture = windowTexture.getTexture();
        sf::Sprite sprite(texture);
        sprite.setPosition(0,0);

        // tidy up the window
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
