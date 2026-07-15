
#include "utils.h"
#include "bigfont.h"

//100 RENDER FOOs

void render_clock(WINDOW *win){
	    werase(win);    
	    box(win, 0, 0);

	    time_t now = time(NULL);
	    struct tm *t = localtime(&now);
	    draw_clock(win,
	        t->tm_hour / 10, t->tm_hour % 10,
	        t->tm_min / 10 , t->tm_min % 10,
		t->tm_sec / 10 , t->tm_sec % 10 );
	    wrefresh(win);
}

void draw_bar(WINDOW *win, int y, int x, int percent)
{
    //TODO RM HARDCODES
    int width = 15;
    int filled = (percent * width) / 100;

    mvwprintw(win, y, x, "[");
    for (int i = 0; i < width; i++)
    {
        if (i < filled)
            //waddwstr(win, L"█");
	    wprintw(win, "█");
        else
            //waddwstr(win, L" ");
	    wprintw(win, " ");
    }

    wprintw(win, "] %3d%%", percent);
}


void sub_win(WINDOW *win, CpuSample *cpu,  BatteryStats *battery, NetworkStats *network){
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "CPU ");
    draw_bar(win, 1, 7, cpu->total);
    mvwprintw(win, 3, 2, "BAT ");
    draw_bar(win, 3, 7, battery->percent);

    mvwprintw(win, 1, 32,
              "UP   %7.1f KB/s",
              network->up);

    mvwprintw(win, 3, 32,
              "DOWN %7.1f KB/s",
              network->down);
    wrefresh(win);
}

#include <stdio.h>
int read_cpu(CpuSample *cpu)
{
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp)
        return 0;

    unsigned long long user, nice, system;
    unsigned long long idle, iowait;
    unsigned long long irq, softirq, steal;

    fscanf(fp,
           "cpu   %llu   %llu     %llu   %llu     %llu  %llu      %llu     %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);

    fclose(fp);
    unsigned long long idle_all = idle + iowait;
    unsigned long long total = user + nice + system + idle + iowait + irq + softirq + steal;

    static unsigned long long prev_idle = 0;
    static unsigned long long prev_total = 0;

    if (prev_total == 0) {
        prev_idle = idle_all;
        prev_total = total;
        cpu->total = 0;
        return 1;
    }

    unsigned long long total_diff = total - prev_total;
    unsigned long long idle_diff  = idle_all - prev_idle;

    cpu->total = (total_diff == 0) ? 0 : (int)((100.0 * (total_diff - idle_diff)) / total_diff);

    prev_idle = idle_all;
    prev_total = total;

    return 1;
}

#include <string.h>

int read_battery(BatteryStats *battery)
{
    FILE *fp;
    
    //TODO DEV SPEC BAT"n" 
    fp = fopen("/sys/class/power_supply/BAT1/capacity", "r");
    if (!fp)
        return 0;

    fscanf(fp, "%d", &battery->percent);
    fclose(fp);

    fp = fopen("/sys/class/power_supply/BAT0/status", "r");
    if (!fp)
        return 0;

    char status[32];
    fscanf(fp, "%31s", status);
    fclose(fp);

    battery->charging = (!strcmp(status, "Charging") || !strcmp(status, "Full"));

    return 1;
}

int read_network(NetworkStats *net, unsigned long long *prev_rx, unsigned long long *prev_tx){
   
   FILE *fp = fopen("/proc/net/dev", "r");
   if (!fp)
        return 0;

    char line[256];
	
    //HEADERS LINEs
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    unsigned long long rx = 0, tx = 0;

    while (fgets(line, sizeof(line), fp))
    {
        char iface[16];
        unsigned long long r, t;

        sscanf(line,
               " %15[^:]: %llu %*u %*u %*u %*u %*u %*u %*u %llu",
               iface, &r, &t);

        if (strcmp(iface, "lo") != 0){
            rx += r;
            tx += t;
        }
    }

    fclose(fp);

    net->down = (rx - *prev_rx) / 1024.0f;
    net->up   = (tx - *prev_tx) / 1024.0f;

    *prev_rx = rx;
    *prev_tx = tx;

    return 1;
}
