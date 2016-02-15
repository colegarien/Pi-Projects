#include "wind_util.h"
#include <ncurses.h>
#include <string>
#include <vector>

#ifndef PIC_WINDOW_H
#define PIC_WINDOW_H

class PictureWindow{
  private:
   WIN window;
   int mapx;	// IN GAME position
   int mapy;	// IN GAME position
   int imgx;	// IN EDITOR position
   int imgy;	// IN EDITOR position
   int curx;	// tile cursor is on
   int cury;	// tile cursor is on
   int twoToOne(int x, int y);
   int oneToX(int i);
   int oneToY(int i);
  public:
   PictureWindow();
   PictureWindow(std::string title);
   PictureWindow(std::string title, int x, int y, int w, int h);
   void setmapxy(int x, int y);
   void generate(int w, int h);
   void move_img(int xshift, int yshift);
   void paint(int tile, int type);
   void draw();
   std::vector<int> tile; // img of the tile
   std::vector<int> type; // floor, wall, door, water ...
   int width;	// # of tiles wide
   int height;	// # of tiles tall
};

#endif
