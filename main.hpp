#include <SFML/Graphics.hpp>

typedef struct enemy {
    int id;
    int tile_id;
    int facing;
    int x;
    int y;
};

typedef struct macro_entity {
    int id;
    int type;   // 0 - missile, 1 - flak
    int facing;
    int x;
    int y;
};

typedef struct asteroid_entity {
    bool type;
    int facing;
    int x;
    int y;
    int mod_vx;
    int mod_vy;
    int data[16];
    int tiles;
};

#define PAD_LEFT 128
#define PAD_RIGHT 128
#define PAD_BOTTOM 128
#define PAD_TOP 128

// map sizing
#define WIDTH 50
#define HEIGHT 35

// screen sizing
#define S_WIDTH 1024
#define S_HEIGHT 576

// tick thresold
#define TICK_THRESHOLD 5

// entity timing constants milliseconds)
#define TIME_ENEMY 1000
#define TIME_MACRO 100
#define TIME_ASTROID 500
#define TIME_CHARACTER 760

// number of enemies
#define ENEMIES 4

// timing
extern double time_macro;
extern double time_asteroid;
extern double time_character;
extern double time_enemy;
extern double time_gif;

// entity defs
extern enemy enemies[ENEMIES];
extern macro_entity macro_entities[64];
extern asteroid_entity asteroids[16];
extern int top_of_entities;
extern int top_of_asteroids;

// direction of asteriod
extern int asteriod_direction;

// time interval
extern double timerval;

// maps
extern int mapdata[HEIGHT][WIDTH];
extern int screen[];

// character attrs
extern int character_x;
extern int character_y;
extern int dx; // for moving towards the edge of the screen
extern int dy; // for moving towards the edge of the screen
extern int facing;
extern int health;
extern float experience;
extern int fuel;
extern int rockets;
extern int rounds;
extern int credits;
extern int sector_x;
extern int sector_y;
extern int sector_s;
extern int level;

// main window texture handle
extern sf::RenderTexture windowTexture;

// game state
extern int state;
