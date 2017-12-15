// internal displays
void display_normal(void);
void display_nav(void);
void display_combat(void);
void display_character(void);
void display_interact(void);
void stat_screen(int i);
void cleardisplay();
void draw_menu(int type);

// main display
void display(bool update, int state);

// util functions
void push_space(int space);
void print(int x, int y, char * c, int len);
int init_displays(void);
int get_terrain(int x, int y);
void set_terrain(int x, int y, int t);

char * strcat(char * dest, char* src);
