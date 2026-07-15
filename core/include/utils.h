#pragma once 
#include "t_config.h"
#include <time.h>
#include <string.h>

/*
 * 100
 */

//TEXT DISP (ALI : POS)
void u_put(ScreenConfig *sc,const char* text, int ali);

//
void u_putU8(WINDOW *win, ScreenConfig *sc, int y, const char *text);

//PREV
void render_clock(WINDOW *win);

//CLOCK BASE
//void sub_win(WINDOW *win, CpuSample *cpu);

void sub_win(WINDOW *win, CpuSample *cpu, BatteryStats *battery, NetworkStats *network);

//STAT
int read_cpu(CpuSample *cpu);
int read_battery(BatteryStats *battery);
int read_network(NetworkStats *network,unsigned long long *prev_rx, unsigned long long *prev_tx);

//BAR
void sub_win(WINDOW *win, CpuSample *cpu, BatteryStats *battery, NetworkStats *network);
void draw_bar(WINDOW *win, int y, int x, int percent);
