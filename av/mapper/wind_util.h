#include <ncurses.h>
#include <string>

#ifndef WIN_UTIL_H
#define WIN_UTIL_H

typedef struct _win_border_struct {
	chtype	ls, rs, ts, bs,
		tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct{
	int startx, starty;
	int height, width;
        std::string title;
	WIN_BORDER border;
}WIN;

void set_win_title(WIN *p_win, std::string title);
void init_win_params(WIN *p_win);
void set_win_dim(WIN *p_win, int x, int y, int w, int h);
void set_win_border(WIN *p_win, char ls,char rs,char ts,char bs,char tl,char tr,char bl,char br);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);

#endif
