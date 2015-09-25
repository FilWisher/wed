#ifndef WED_H
#define WED_H

#include "position.h"

Position make_position(int, int);
Position compute_change(Position, Position);
void draw_coords(WINDOW *, Position);
void draw_text(WINDOW *, char []);

#endif
