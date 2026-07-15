#pragma once 

#include <ncurses.h>
#include "utils.h"

#define FONT_HEIGHT 7
#define FONT_WIDTH  5

//FONTS
extern const char *digits[10][FONT_HEIGHT];

//CLOCK DISP
void draw_clock(WINDOW *win, int h1, int h2, int m1, int m2, int s1 , int s2);

//void draw_text(WINDOW *win, int y, int x, const char *text);
//void draw_digit(WINDOW *win, int y, int x, int number);

