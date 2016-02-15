#include "tool_window.h"
#include "wind_util.h"
#include <ncurses.h>
#include <string>

using namespace std;

ToolWindow::ToolWindow(){
  set_win_title(&window,"TOOL WINDOW");
  init_win_params(&window);
  set_win_dim(&window,0,0,10,10);
  mapw = 10;
  maph = 10;
  tile = 0;
  type = 0;
  mapx = 0;
  mapy = 0;
  curitem = 0;
}
ToolWindow::ToolWindow(string title){
  set_win_title(&window,title);
  init_win_params(&window);
  set_win_dim(&window,0,0,10,10);
  mapw = 10;
  maph = 10;
  tile = 0;
  type = 0;
  mapx = 0;
  mapy = 0;
  curitem = 0;
}
ToolWindow::ToolWindow(string title, int x, int y, int w, int h){
  set_win_title(&window,title);
  init_win_params(&window);
  set_win_dim(&window,x,y,w,h);
  mapw = 10;
  maph = 10;
  tile = 0;
  type = 0;
  mapx = 0;
  mapy = 0;
  curitem = 0;
}
void ToolWindow::draw(){
  create_box(&window, false);
  create_box(&window, true);

  // DRAW TOOLS AND STUFF
  if (curitem == 0) attron(A_REVERSE);
  mvprintw(window.starty+2,window.startx+2,"MapX: %d", mapx);
  attroff(A_REVERSE);
  if (curitem == 1) attron(A_REVERSE);
  mvprintw(window.starty+4,window.startx+2,"MapY: %d", mapy);
  attroff(A_REVERSE);
  if (curitem == 2) attron(A_REVERSE);
  mvprintw(window.starty+6,window.startx+2,"MapW: %d", mapw);
  attroff(A_REVERSE);
  if (curitem == 3) attron(A_REVERSE);
  mvprintw(window.starty+8,window.startx+2,"MapH: %d", maph);
  attroff(A_REVERSE);
  if (curitem == 4) attron(A_REVERSE);
  mvprintw(window.starty+10,window.startx+2,"TILE: %d (%c)", tile, char(tile%75+48));
  attroff(A_REVERSE);
  if (curitem == 5) attron(A_REVERSE);
  mvprintw(window.starty+12,window.startx+2,"TYPE: ");
  attron(COLOR_PAIR(type%7));
  mvprintw(window.starty+12,window.startx+8,"%d", type);
  attroff(COLOR_PAIR(type%7));
  attroff(A_REVERSE);
  if (curitem == 6) attron(A_REVERSE);
  mvprintw(window.starty+14,window.startx+2,"-GENERATE-");
  attroff(A_REVERSE);
  if (curitem == 7) attron(A_REVERSE);
  mvprintw(window.starty+16,window.startx+2,"-SAVE-");
  attroff(A_REVERSE);
}
void ToolWindow::key_up(){
  curitem--;
  if (curitem<0) curitem = 7;
}
void ToolWindow::key_down(){
  curitem++;
  if (curitem>7) curitem = 0;
}
void ToolWindow::key_left(){
  if(curitem == 0){
    mapx--;
    if (mapx<0)
      mapx=255;
  }else if(curitem == 1){
    mapy--;
    if (mapy<0)
      mapy=255;
  }else if(curitem == 2){
    mapw--;
    if (mapw<1)
      mapw=256;
  }else if(curitem == 3){
    maph--;
    if (maph<1)
      maph=256;
  }else if(curitem == 4){
    tile--;
    if (tile<0)
      tile=255;
  }else if(curitem == 5){
    type--;
    if (type<0)
      type=255;
  }else if(curitem == 6){
  }
}
void ToolWindow::key_right(){
  if(curitem == 0){
    mapx++;
    if (mapx>255)
      mapx=0;
  }else if(curitem == 1){
    mapy++;
    if (mapy>255)
      mapy=0;
  }else if(curitem == 2){
    mapw++;
    if (mapw>256)
      mapw=1;
  }else if(curitem == 3){
    maph++;
    if (maph>256)
      maph=1;
  }else if(curitem == 4){
    tile++;
    if (tile>255)
      tile=0;
  }else if(curitem == 5){
    type++;
    if (type>255)
      type=0;
  }else if(curitem == 6){
  }
}
bool ToolWindow::key_space(){
  if (curitem == 6 || curitem == 7)
    return true;
  return false;
}
