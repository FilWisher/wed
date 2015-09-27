#ifndef ui_h
#define ui_h

#include <ncurses.h>
#include "position.c"

void draw_text(WINDOW *win, char *text);
void draw_coords(WINDOW *, Position);

#endif
