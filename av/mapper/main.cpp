#include <ncurses.h>
#include <string>
#include <fstream>
#include <sstream>
#include "wind_util.h"
#include "pic_window.h"
#include "tool_window.h"

using namespace std;

#define QUIT_KEY 27
#define SWITCH_KEY 9
#define MAP_KEY 0
#define TOOL_KEY 1  
#define LEFT_KEY 260
#define RIGHT_KEY 261
#define UP_KEY 259
#define DOWN_KEY 258
#define SPACE_KEY 32

int main(){
  // input character
  int ch;
  int row,col;
  int active = MAP_KEY;
  
  // intialize NCurses
  initscr();	// starter up
  getmaxyx(stdscr,row,col);   // get number of rows and columns
  start_color();// so color can be used
  curs_set(0);	// hides the 'cursor'
  raw();	// line buffer disabled
  keypad(stdscr, TRUE);
  noecho();	// as button pressed don't display

  init_pair(1, COLOR_RED, COLOR_BLACK);  
  init_pair(2, COLOR_GREEN, COLOR_BLACK);  
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);  
  init_pair(4, COLOR_BLUE, COLOR_BLACK);  
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);  
  init_pair(6, COLOR_CYAN, COLOR_BLACK);  

  // intialize Windows
  PictureWindow map_win("MAP WINDOW", 0,0,col*.66,row-2);
  ToolWindow tool_win("TOOLS WINDOW",col*.66,0,col-col*.66,row-2);
  
  // draw windows to screen buffer
  map_win.draw();
  tool_win.draw();
  
  // Update the console screen
  refresh();
  
  // MAIN PROGRAM LOOP
  while((ch = getch())!=QUIT_KEY){
    mvprintw(row-1,col-12,"            ");
    mvprintw(row-1,2," KEY: %d   ",ch);
    if (active==TOOL_KEY){
      if (ch == SWITCH_KEY){
        active=MAP_KEY;
        mvprintw(row-1,14," ACTIVE: map   ");
      }else if(ch == LEFT_KEY){
        tool_win.key_left();
        tool_win.draw();
      }else if(ch == RIGHT_KEY){
        tool_win.key_right();
        tool_win.draw();
      }else if(ch == UP_KEY){
        tool_win.key_up();
        tool_win.draw();
      }else if(ch == DOWN_KEY){
        tool_win.key_down();
        tool_win.draw();
      }else if(ch == SPACE_KEY){
        if(tool_win.key_space()){
          if(tool_win.curitem == 6){
            map_win.generate(tool_win.mapw, tool_win.maph);
            map_win.draw();
          }else{
            stringstream ss;
            ss << "maps/" << tool_win.mapx << tool_win.mapy;
            
            ofstream fout;
            fout.open(ss.str().c_str(), ios::binary | ios::out);
            
            fout.write((char*)&(tool_win.mapx), sizeof(char));
            fout.write((char*)&(tool_win.mapy), sizeof(char));
            fout.write((char*)&(tool_win.mapw), sizeof(char));
            fout.write((char*)&(tool_win.maph), sizeof(char));
            for (int i = 0; i < map_win.width*map_win.height; i++)
              fout.write((char*)&(map_win.tile[i]), sizeof(char));
            
            fout.close();
            mvprintw(row-1,col-12," FILE SAVED ");
          }
        }
      }
    }else if(active==MAP_KEY){
      if (ch == SWITCH_KEY){
        active=TOOL_KEY;
        mvprintw(row-1,14," ACTIVE: tool  ");
      }else if(ch == LEFT_KEY){
        map_win.move_img(-1, 0);
        map_win.draw();
      }else if(ch == RIGHT_KEY){
        map_win.move_img(1, 0);
        map_win.draw();
      }else if(ch == UP_KEY){
        map_win.move_img(0,-1);
        map_win.draw();
      }else if(ch == DOWN_KEY){
        map_win.move_img(0,1);
        map_win.draw();
      }else if(ch == SPACE_KEY){
        map_win.paint(tool_win.tile, tool_win.type);
        map_win.draw();
      }
    }
  }
  
  // clean/close NCurses
  endwin();
  return 0;
}
