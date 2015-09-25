#ifndef WED_H
#define WED_H

typedef struct Position {
  int x;
  int y;
} Position;

Position make_position(int, int);
Position get_new_position(Position, int);
Position compute_change(Position, Position);
int out_of_bounds(Position, int, int);
void draw_coords(WINDOW *, Position);
void draw_text(WINDOW *, char []);

#endif
