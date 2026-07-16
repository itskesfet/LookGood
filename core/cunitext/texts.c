#include "bigfont.h"


/*
 *
 * Fonts And Disp
 * 100(CHARS,CLOCK DRAW)
 *
 *
 */


const char *colon[FONT_HEIGHT] = {
    "     ",
    "  █  ",
    "     ",
    "     ",
    "  █  ",
    "     ",
    "     "
};



//Clock
#define CLOCK_WIN_HEIGHT 11
#define CLOCK_WIN_WIDTH 57
#define CLOCK_CONTENT_WIDTH 51

void draw_clock(WINDOW *win, int h1, int h2, int m1, int m2, int s1 , int s2)
{
    int x = (CLOCK_WIN_WIDTH - 2 - CLOCK_CONTENT_WIDTH) / 2 + 1;
    int y = 2; //To Do

    for (int row = 0; row < FONT_HEIGHT; row++)
    {
        mvwprintw(win, row + y, x, "%s %s  %s  %s %s %s %s %s",
            digits[h1][row],
            digits[h2][row],
            colon[row],
            digits[m1][row],
            digits[m2][row],
	    colon[row],
            digits[s1][row],
            digits[s2][row]
        );
    }
}
//clock
const char *digits[10][FONT_HEIGHT] = {

    // 0
    {
        " ███ ",
        "█   █",
        "█  ██",
        "█ █ █",
        "██  █",
        "█   █",
        " ███ "
    },

    // 1
    {
        "  █  ",
        " ██  ",
        "  █  ",
        "  █  ",
        "  █  ",
        "  █  ",
        "█████"
    },

    // 2
    {
        " ███ ",
        "█   █",
        "    █",
        "   █ ",
        "  █  ",
        " █   ",
        "█████"
    },

    // 3
    {
        "████ ",
        "    █",
        "    █",
        " ███ ",
        "    █",
        "    █",
        "████ "
    },

    // 4
    {
        "█  █ ",
        "█  █ ",
        "█  █ ",
        "█████",
        "   █ ",
        "   █ ",
        "   █ "
    },

    // 5
    {
        "█████",
        "█    ",
        "█    ",
        "████ ",
        "    █",
        "    █",
        "████ "
    },

    // 6
    {
        " ███ ",
        "█    ",
        "█    ",
        "████ ",
        "█   █",
        "█   █",
        " ███ "
    },

    // 7
    {
        "█████",
        "    █",
        "   █ ",
        "  █  ",
        " █   ",
        " █   ",
        " █   "
    },

    // 8
    {
        " ███ ",
        "█   █",
        "█   █",
        " ███ ",
        "█   █",
        "█   █",
        " ███ "
    },

    // 9
    {
        " ███ ",
        "█   █",
        "█   █",
        " ████",
        "    █",
        "    █",
        " ███ "
    }

};
