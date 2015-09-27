#include "position.c"

Position compute_change(Position pos, Position change)
{
  pos.x += change.x;
  pos.y += change.y;
  return pos;
}

int out_of_bounds(Position pos, int x_bound, int y_bound) {
  if (pos.x > x_bound || pos.x < 0 || pos.y > y_bound-1 || pos.y < 0) return 1;
  else return 0;
}

Position move (Position cur_pos, Position change, int scale)
{
  Position old_pos = cur_pos;
  Position scaled_translate = { change.x*scale, change.y*scale };
  Position pos = compute_change(cur_pos, scaled_translate);
  
  if (out_of_bounds(pos, X_MAX-1, Y_MAX-1)) pos = old_pos;

  return pos;
}

Position move_left (Position pos)
{
  return move(pos, make_position(-1, 0), 1);
} 

Position move_right (Position pos)
{
  return move(pos, make_position(1, 0), 1);
}

Position move_down (Position pos)
{
  return move(pos, make_position(0, 1), 1);
}

Position move_up (Position pos)
{
  return move(pos, make_position(0, -1), 1);
}
