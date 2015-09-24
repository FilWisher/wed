#include <stdio.h>
#include <curses.h>
#include <string.h>

#include "config.h"
#include "wed.h"

void draw_coords(WINDOW *win, Position cur_pos) {

  char x_pos[20], y_pos[20], coords[40];
  snprintf(x_pos, sizeof(x_pos), "%d", cur_pos.x);
  snprintf(y_pos, sizeof(y_pos), "%d", cur_pos.y);
  strcpy(coords, x_pos);
  strcat(coords, ",");
  strcat(coords, y_pos);
  wmove(win, Y_MAX-1, (X_MAX*2)/3);
  wprintw(win, coords);
}

Position make_position(int x, int y)
{
  Position pos = {x, y};
  return pos;
}

int out_of_bounds(Position pos, int x_bound, int y_bound) {
  if (pos.x > x_bound || pos.x < 0 || pos.y > y_bound-1 || pos.y < 0)
    return 1;
  else
    return 0;
}

Position get_new_position(Position pos, int ch)
{
  Position old_pos = pos;
  switch (ch) {
    case 'h':
      pos = compute_change(pos, make_position(-1, 0));
      break;
    case 'l':
      pos = compute_change(pos, make_position(1, 0));
      break;
    case 'j':
      pos = compute_change(pos, make_position(0, 1));
      break;
    case 'k':
      pos = compute_change(pos, make_position(0, -1));
      break;
    default:
      pos = make_position(0, 0);
  }
  
  if (out_of_bounds(pos, X_MAX-1, Y_MAX-1))
    pos = old_pos;
    
  
  return pos;
}

Position compute_change(Position pos, Position change)
{
  pos.x += change.x;
  pos.y += change.y;
  return pos;
}

void draw_text(WINDOW *win, char *text) {
	int i;
	size_t text_length = strlen(text); 
	wmove(win, 0, 0);
	for (i = 0; i < text_length; i++) {
		waddch(win, text[i]);
	}
}

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
