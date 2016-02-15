#include "wind_util.h"
#include <ncurses.h>
#include <string>

#ifndef TOOL_WINDOW_H
#define TOOL_WINDOW_H

class ToolWindow{
  private:
   WIN window;
  public:
   ToolWindow();
   ToolWindow(std::string title);
   ToolWindow(std::string title, int x, int y, int w, int h);
   void key_left();
   void key_right();
   void key_up();
   void key_down();
   bool key_space();
   void draw();
   int tile;
   int type;
   int mapx;
   int mapy;
   int mapw;
   int maph;
   int curitem;
};

#endif
