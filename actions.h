#ifndef actions_h
#define actions_h

#include "position.c"

Position compute_change(Position, Position);
int out_of_bounds(Position, int, int);
Position move(Position, Position, int);
Position move_left(Position);
Position move_right(Position);
Position move_up(Position);
Position move_down(Position);

#endif
