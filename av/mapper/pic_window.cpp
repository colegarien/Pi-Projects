#include "pic_window.h"
#include "wind_util.h"
#include <ncurses.h>
#include <string>
#include <vector>

using namespace std;

PictureWindow::PictureWindow(){
  set_win_title(&window,"PICTURE WINDOW");
  init_win_params(&window);
  set_win_dim(&window,0,0,10,10);
  generate(10,10);
}
PictureWindow::PictureWindow(string title){
  set_win_title(&window,title);
  init_win_params(&window);
  set_win_dim(&window,0,0,10,10);
  generate(10,10);
}
PictureWindow::PictureWindow(string title, int x, int y, int w, int h){
  set_win_title(&window,title);
  init_win_params(&window);
  set_win_dim(&window,x,y,w,h);
  generate(10,10);
}
void PictureWindow::setmapxy(int x, int y){
  mapx = x;
  mapy = y;
}
void PictureWindow::generate(int w, int h){
  width = w;
  height = h;
  imgx = (-window.width+2)/2;
  imgy = (-window.height+2)/2;
  curx = 0;
  cury = 0;
  tile.clear();
  type.clear();
  for (int i = 0; i < width*height; i++){
    tile.push_back(0);
    type.push_back(0);
  }
}
void PictureWindow::draw(){
  create_box(&window, false);
  create_box(&window, true);

  // DRAW CODE FOR MAP HERE
  int xini = imgx;
  int yini = imgy;
  int xmax = xini+window.width -1;
  int ymax = yini+window.height -1;
  for (int x = xini; x < xmax; x++){
    for(int y = yini; y < ymax; y++){
      // COLOR CODE GOES HERE
      if (x>=0 && y>=0 && x<width && y<height){
        attron(COLOR_PAIR(type[twoToOne(x,y)]%7));
        if (curx == x && cury == y)
          mvaddch(window.starty+1+y-yini,window.startx+1+x-xini,char(tile[twoToOne(x,y)]+48) | A_REVERSE);
        else
          mvaddch(window.starty+1+y-yini,window.startx+1+x-xini,char(tile[twoToOne(x,y)]+48));
        attroff(COLOR_PAIR(type[twoToOne(x,y)]));
      }
    }
  }
}
void PictureWindow::move_img(int xshift, int yshift){
  if (imgx + xshift >= (-window.width+2)/2 && imgx + xshift < width/2)
    imgx += xshift;
  if (imgy + yshift >= (-window.height+2)/2 && imgy + yshift <  height/2)
    imgy += yshift;
  if (curx+xshift >= 0 && curx+xshift < width)
    curx+=xshift;
  if (cury+yshift >= 0 && cury+yshift < height)
    cury+=yshift;
}
void PictureWindow::paint(int tile, int type){
  this->tile[twoToOne(curx, cury)] = tile;
  this->type[twoToOne(curx, cury)] = type;
}
int PictureWindow::twoToOne(int x, int y){
  return x + y * width;
}
int PictureWindow::oneToX(int i){
  return i % width;
}
int PictureWindow::oneToY(int i){
  return i / width;
}
