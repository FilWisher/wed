#include <stdio.h>
#include <string.h>

#include "ui.h"

void draw_text(WINDOW *win, char *text) {
  int i;
  size_t text_length = strlen(text); 
  wmove(win, 0, 0);
  for (i = 0; i < text_length; i++) {
    waddch(win, text[i]);
  }
}

void draw_coords(WINDOW *win, Position cur_pos)
{
  char x_pos[20], y_pos[20], coords[40];
  snprintf(x_pos, sizeof(x_pos), "%d", cur_pos.x);
  snprintf(y_pos, sizeof(y_pos), "%d", cur_pos.y);
  strcpy(coords, x_pos);
  strcat(coords, ",");
  strcat(coords, y_pos);
  wmove(win, Y_MAX-1, (X_MAX*2)/3);
  wprintw(win, coords);  
}