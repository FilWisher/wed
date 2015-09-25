#ifndef keyevents_h
#define keyevents_h

#include "position.h"

int out_of_bounds(Position, int, int);
Position get_new_position(Position, int);
Position compute_change(Position, Position);

#endif