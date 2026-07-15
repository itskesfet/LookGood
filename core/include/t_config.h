#include <ncurses.h>

/*
 * 100
 *
 * */
//==============================================
//	TTY TEMP.
typedef struct {
    int width;
    int height;

    bool border;
    short fg_color;
    short bg_color;

    char border_horizontal;
    char border_vertical;
    char border_corner;

    char title[64];

    bool show_clock;
    bool show_cpu;
    bool show_memory;
} ScreenConfig;



typedef struct {
    WINDOW *window;
    int current_width;
    int current_height;
    bool needs_redraw;
} Screen;


//==============================================

//	UTILS 	

typedef struct {
    int percent;
    int charging;
} BatteryStats;

typedef struct {
    unsigned long long total;
    unsigned long long idle;
} CpuSample;


//==============================================


//	STATS BAR STR

typedef struct {
    float usage;
} CpuStats;

typedef struct {
    float up;
    float down;
} NetworkStats;
/*
typedef struct {
    int percent;
    int charging;
} BatteryStat;
*/
typedef struct {
    float temperature;
} WeatherStats;

typedef struct {
    CpuStats cpu;
    NetworkStats network;
    BatteryStats battery;
    WeatherStats weather;
} Stats;

typedef struct {
    CpuStats cpu;
    NetworkStats network;
    BatteryStats battery;
    WeatherStats weather;
} t_Stats;

//==============================================

