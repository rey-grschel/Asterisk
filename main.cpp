#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "main.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "entity.hpp"
using namespace std;

// timer
double timerval = 0;
double time_macro = 0;
double time_asteroid = -1000;
double time_character = 0;
double time_enemy = 0;
double time_gif = 0;

// enemy defs
enemy enemies[ENEMIES];
macro_entity macro_entities[64];
asteroid_entity asteroids[16];
int top_of_entities = 0;
int asteriod_direction = 0;
int top_of_asteroids = 0;

// map and screen sizing
int mapdata[HEIGHT][WIDTH];
int screen[S_WIDTH * S_HEIGHT];

// game state: 0 - normal, 1 - ship nav, 2 - combat screen, 3 - character, 4 - port / entity interact
int displaystate = 0;

// character health
int health = 500;

// character experience
float experience = 0;

// character location
int character_x = 50;
int character_y = 50;
int facing = 0;

// game state
// 0: main map, 1: view, 2: selecting view, 3: view selected, 4: interacting, 5: mod self, 6: mod self confirm
int state = 0;

// texture
sf::RenderTexture windowTexture;

int main(){
//    asteriod_direction = 0;

    // set up events
    sf::Event event;

    // initalize rand
    srand (time(NULL));

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
    generate_level();

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);

    // main loop
    while (window.isOpen()){
        // clean texture
        windowTexture.clear();

        // update timer
        elapsed = clock.restart();
        time_asteroid += elapsed.asMilliseconds();
        time_character += elapsed.asMilliseconds();
        time_macro += elapsed.asMilliseconds();
        time_enemy += elapsed.asMilliseconds();
        time_gif += elapsed.asMicroseconds();

        // handle events
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Num1) {
                    state = 0;
                } else if (event.key.code == sf::Keyboard::Num2) {
                    state = 1;
                } else if (event.key.code == sf::Keyboard::Num0) {
                    state = -1;
                }

                if (event.key.code == sf::Keyboard::V){
                    state = 2;
                    cout << "State: " << state << endl;
                }

                if (event.key.code == sf::Keyboard::A){
                    top_of_entities = 0;
                }

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
                    if (top_of_entities < 64){
                        macro_entities[top_of_entities].facing = facing;
                        macro_entities[top_of_entities].x = character_x;
                        macro_entities[top_of_entities].y = character_y;
                        macro_entities[top_of_entities].type = 0;
                        macro_entities[top_of_entities].id = top_of_entities + rand() % 128;
                        top_of_entities++;
                    }
                }

                if (event.key.shift){
                    facing += 4;
                } else {
                }
            }
        }

        // exit
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            return 0;
        }

        //update everything
        if (state == 0){
            update_enemies();
            update_asteroids();
            update_macro();
        }

        // draw time
        char tim[20];
        text.setString("Time: ");
        text.setPosition(816, S_HEIGHT - 18);
        windowTexture.draw(text);
        sprintf(tim, "%d", elapsed );
        text.setString(tim);
        text.setPosition(900, S_HEIGHT - 16);
        windowTexture.draw(text);
        sprintf(tim, "%d", time_asteroid );
        text.setString(tim);
        text.setPosition(960, S_HEIGHT - 16);
        windowTexture.draw(text);

        // display main texture
        windowTexture.setSmooth(true);
        windowTexture.display();
        const sf::Texture& texture = windowTexture.getTexture();
        sf::Sprite sprite(texture);
        sprite.setPosition(1,1);

        // draw screen
        if (state == 0 || state == 2){
            display(false, 0);
        } else if (state == 1){
            draw_menu(0);
        } else {
            cleardisplay();
        }

        // tidy up the window
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
