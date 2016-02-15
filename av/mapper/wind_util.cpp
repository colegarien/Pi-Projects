#include "wind_util.h"
#include <ncurses.h>
#include <string>

using namespace std;

void set_win_title(WIN *p_win, string title){
  p_win->title = title;
}

void init_win_params(WIN *p_win){
  p_win->height = 0;
  p_win->width = 0;
  p_win->startx = 10;
  p_win->starty = 10;

  p_win->border.ls = '|';
  p_win->border.rs = '|';
  p_win->border.ts = '-';
  p_win->border.bs = '-';
  p_win->border.tl = '+';
  p_win->border.tr = '+';
  p_win->border.bl = '+';
  p_win->border.br = '+';
}
void set_win_dim(WIN *p_win, int x, int y, int w, int h){
  p_win->height = h;
  p_win->width = w;
  p_win->startx = x;
  p_win->starty = y;
}
void set_win_border(WIN *p_win, char ls,char rs,char ts,char bs,char tl,char tr,char bl,char br){
  p_win->border.ls = ls;
  p_win->border.rs = rs;
  p_win->border.ts = ts;
  p_win->border.bs = bs;
  p_win->border.tl = tl;
  p_win->border.tr = tr;
  p_win->border.bl = bl;
  p_win->border.br = br;
}

void print_win_params(WIN *p_win){
#ifdef _DEBUG
  mvprintw(25,0,"%d %d %d %d", p_win->startx, p_win->starty, p_win->width, p_win->height);
  refresh();
#endif
}

void create_box(WIN *p_win, bool flag){
  int x,y,w,h;
  x = p_win->startx;
  y = p_win->starty;
  w = p_win->width;
  h = p_win->height;

  if(flag){
    // draw corners
    mvaddch(y,x,p_win->border.tl);
    mvaddch(y,x+w,p_win->border.tr);
    mvaddch(y+h,x,p_win->border.bl);
    mvaddch(y+h,x+w,p_win->border.br);
    
    // draw borders
    mvhline(y,x+1,p_win->border.ts,w-1);
    mvhline(y+h,x+1,p_win->border.bs,w-1);
    mvvline(y+1,x,p_win->border.ls,h-1);
    mvvline(y+1,x+w,p_win->border.rs,h-1);
    
    // add title
    int titlebar_len = w-3;
    if (p_win->title!="" && titlebar_len>0){
      if(p_win->title.length() < w-2)
        mvprintw(y,x+2,p_win->title.c_str());
      else
        mvprintw(y,x+2,p_win->title.substr(0, titlebar_len).c_str());
    }
  }else {
    for(int j = y; j <= y+h; j++){
      for(int i = x; i <= x+w; i++){
        mvaddch(j,i,' ');
      }
    }
  }
  refresh();
}
