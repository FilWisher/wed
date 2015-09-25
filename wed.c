#include <stdio.h>
#include <curses.h>
#include <string.h>

#include "config.h"
#include "wed.h"
#include "keyevents.c"
#include "position.c"

int main (void)
{
  
  WINDOW *win;
  
  Position cur_pos = make_position(1, 0); 
  int ch = 0;
  
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  win=newwin(12,40,0,0);
  wmove(win, 0, 5);
  wbkgd(win, COLOR_PAIR(1));
  
  while(ch != 1) {

    cur_pos = get_new_position(cur_pos, getch());
    win=newwin(Y_MAX,X_MAX,0,0);
    draw_coords(win, cur_pos);
    draw_text(win, "Hey hjkl\nI am some mock text\n\nDAAAAYMN!!!");
    wmove(win, cur_pos.y, cur_pos.x);
    wbkgd(win, COLOR_PAIR(1));
    wrefresh(win);
  }
  delwin(win);
  endwin();
}
