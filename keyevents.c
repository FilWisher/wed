#include "keyevents.h"
#include "position.c"

Position compute_change(Position pos, Position change)
{
  pos.x += change.x;
  pos.y += change.y;
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