#ifndef PACMAN_H
#define PACMAN_H
const int wall_height = 10;
const int wall_width = 10;
const int image_sizeh = 30;
const int image_sizew = 30;
// window
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Hello World";

// map
const int max_row = 15;
const int max_col = 42;
const char mapp[max_row][max_col] = {
"000000000000000000000",
"011111111111111111110",
"010000111101111000010",
"011110111000111011110",
"011110111101111011110",
"011111111111111111110",
"011111110   011111110",
"010000110234011000010",
"011111110000011111110",
"011110111111111011110",
"011110100000001011110",
"01000010  5  01000010",
"011111111111111111110",
"000000000000000000000"
};


#endif
