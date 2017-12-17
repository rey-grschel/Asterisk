/*
===================================================================================================
Level Definition Guidelines:
===================================================================================================
const int level_X_S[10][10] is the definition for the warp quadrant.
        X is the level number and S is the sector (0 - 3)
        Values 0 - 4 are allowed:
            0: Nothing
            1: Station
            2: Ice field
            4: Nebula
            4: Planetary System
const level_data * level_X_S_N_level_data is a variable length array of data for flight level view
        N is the corresponding entry number in the corresponding level_X_S_tile_data array
        The type field in struct level_data defines the following values
            0: station
            1: asteroid group
            2: enemy
            3: debris
        if the type is 1 or 3 then the last value, char num, must be the number of the asteroids or debris wanted.
const tile_data level_0_0_tile_data[10] is the data for viewing at the pre-warp level. There must be 10 and only ten entries that have detailed info.
        If an undefined tile is warped to (meaning there is no corresponding tile_data object for it, an empty asteroid field will be generated,
            along with suitable "flavor" material
*/

/*
===================================================================================================
struct definitions:
===================================================================================================
*/
// for flight level view
typedef struct level_data {
    int x;
    int y;
    char data[16];
    bool persistent;
    char type;
    unsigned char num;
};

// for info on each tile in sector
typedef struct tile_data {
    int x;
    int y;
    char data[16];
    char num_level_data;
    level_data flight_data[];
};

/*
===================================================================================================
LEVEL 0 DATA - Epsilon Quadrant
===================================================================================================
*/
const int level_0_0[10][10] = { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                { 0, 0, 0, 0, 0, 3, 0, 0, 0, 0},
                                { 0, 1, 0, 3, 3, 0, 0, 0, 0, 0},
                                { 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
                                { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                                { 0, 0, 0, 0, 0, 0, 0, 4, 0, 0},
                                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                { 0, 0, 2, 0, 0, 0, 0, 0, 1, 0},
                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                { 0, 0, 4, 0, 0, 0, 0, 0, 0, 0}};

const level_data level_0_0_0_level_data[] = { {30, 30, "Abandoned C. R.", true, 0, 0},
                                            {31, 31, "Asteroids", false, 1, 10},
                                            {23, 7, "Debris", false, 3, 5}};

const level_data level_0_0_1_level_data[] = { {30, 30, "Asteroids", true, 1, 20}};

const tile_data level_0_0_tile_data[10] = { {0, 0, "Abandoned C. R.", 3, level_0_0_0_level_data},
                                            {1, 2, "Abandoned C. R.", 3, level_0_0_0_level_data},
                                            {7, 5, "Gau-4 System", 1, level_0_0_1_level_data},
                                            {6, 0, "Tin mining base", 3, level_0_0_1_level_data},
                                            {2, 9, "Gau-13 System", 3, level_0_0_1_level_data},
                                            {3, 4, "Abandoned C. R.", 3, level_0_0_1_level_data},
                                            {9, 6, "Tr. Post 143-k", 3, level_0_0_1_level_data},
                                            {8, 7, "Abandoned Rs. S.", 3, level_0_0_1_level_data},
                                            {4, 2, "Horse Nebula", 3, level_0_0_1_level_data},
                                            {5, 1, "Camel Nebula", 3, level_0_0_1_level_data}};

const int level_0_1[10][10] = { { 0, 0, 0, 0, 0, 0, 0, 3, 3, 4},
                        { 0, 0, 0, 1, 0, 0, 0, 0, 3, 1},
                        { 0, 0, 2, 0, 0, 0, 0, 3, 3, 0},
                        { 0, 1, 2, 0, 0, 0, 3, 3, 4, 0},
                        { 0, 2, 0, 0, 0, 3, 3, 0, 0, 0},
                        { 0, 0, 0, 0, 4, 3, 0, 0, 0, 0},
                        { 0, 0, 3, 3, 3, 3, 3, 3, 2, 0},
                        { 0, 0, 3, 3, 0, 0, 0, 0, 0, 0},
                        { 0, 3, 4, 0, 0, 0, 2, 0, 2, 0},
                        { 4, 0, 0, 0, 0, 0, 0, 0, 2, 1}};

const int level_0_2[10][10] = { { 0, 2, 2, 0, 0, 0, 0, 0, 0, 0},
                        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                        { 0, 0, 0, 0, 1, 0, 2, 0, 0, 0},
                        { 0, 0, 0, 3, 3, 3, 0, 0, 3, 0},
                        { 0, 0, 0, 0, 3, 4, 0, 3, 0, 0},
                        { 0, 0, 2, 3, 3, 3, 3, 3, 0, 0},
                        { 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
                        { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0},
                        { 0, 0, 0, 0, 2, 0, 2, 2, 0, 0},
                        { 0, 0, 0, 0, 0, 2, 0, 0, 0, 1}};

const int level_0_3[10][10] = { { 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                        { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
                        { 0, 0, 0, 0, 0, 2, 2, 0, 0, 0},
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        { 1, 0, 0, 0, 1, 2, 0, 0, 0, 0},
                        { 0, 0, 0, 0, 2, 2, 2, 0, 0, 0},
                        { 0, 2, 0, 0, 0, 0, 2, 3, 0, 3},
                        { 0, 2, 2, 0, 0, 0, 0, 3, 3, 0},
                        { 3, 3, 2, 0, 0, 0, 0, 0, 3, 3},
                        { 4, 3, 0, 0, 0, 0, 0, 0, 3, 3}};


/*
===================================================================================================
LEVEL 0 DATA - Epsilon Quadrant
===================================================================================================
*/
