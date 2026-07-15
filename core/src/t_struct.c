#include <locale.h>
#include <unistd.h>
#include <time.h>
//#include <system.h>
#include "utils.h"
#include "bigfont.h"

//clock
#define CLOCK_WIN_HEIGHT 11
#define CLOCK_WIN_WIDTH  57

//TODO MAKE EM MODUlAR 
int main(void) {
	setlocale(LC_ALL, "");
	initscr();            
	start_color();	
	ScreenConfig  sc;
	
	getmaxyx(stdscr, sc.height, sc.width);	
	refresh(); 
	int _y = (sc.height - CLOCK_WIN_HEIGHT) / 2;
	int _x = (sc.width - CLOCK_WIN_WIDTH) / 2;

	//CLOCK WORK
	WINDOW *win;
    	win = newwin(CLOCK_WIN_HEIGHT, CLOCK_WIN_WIDTH, _y, _x);
	start_color();
   	box(win, 0, 0);
    	wrefresh(win);

	//Stats Work		
	int _y2 = _y + CLOCK_WIN_HEIGHT;
	WINDOW *win2;
    	win2 = newwin(CLOCK_WIN_HEIGHT/1.8, CLOCK_WIN_WIDTH, _y2, _x);
	box(win2,0,0);
	wrefresh(win2);

	CpuSample cStat;	
	BatteryStats battery;
	NetworkStats network;
	unsigned long long prev_rx = 0;
	unsigned long long prev_tx = 0;
	
	while (1)
	{
		read_cpu(&cStat);
    		read_battery(&battery);
		read_network(&network, &prev_rx, &prev_tx);
		render_clock(win);
		sub_win(win2, &cStat, &battery, &network);
    		sleep(1);
	}
    	wrefresh(win);
	getch();
    	delwin(win);	

	getch();                
    	endwin();               
    	return 0;
}
