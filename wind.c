#include <stdio.h>
#include <curses.h>

#define X_MAX 12
#define Y_MAX 40
#define COORD_X 6
#define COORD_Y 20

typedef struct Position Position;

struct Position {
  int x;
  int y;
};

Position make_position(int, int);
Position get_new_positio(Position, int);
Position compute_change(Position, Position);
int out_of_bounds(Position, int, int);
void draw_coords(WINDOW *, Position, int, int);

void draw_coords(WINDOW *vin, Position cur_pos, int x, int y) {

  char x_pos[20], y_pos[20], coords[40];
  snprintf(x_pos, sizeof(x_pos), "%d", cur_pos.x);
  snprintf(y_pos, sizeof(y_pos), "%d", cur_pos.y);
  strcpy(coords, x_pos);
  strcat(coords, y_pos);
  wmove(vin, COORD_Y, COORD_X);
  wprintw(vin, coords);
}

Position make_position(int x, int y)
{
  Position pos = {x, y};
  return pos;
}

int out_of_bounds(Position pos, int x_bound, int y_bound) {
  if (pos.x > x_bound || pos.x < 0 || pos.y > y_bound || pos.y < 0)
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
  
  if (out_of_bounds(pos, X_MAX, Y_MAX-1))
    pos = old_pos;
    
  
  return pos;
}

Position compute_change(Position pos, Position change)
{
  pos.x += change.x;
  pos.y += change.y;
  return pos;
}

int main (void)
{
  
  WINDOW *vin;
  
  Position cur_pos = make_position(1, 0); 
  int ch = 0;
  
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  vin=newwin(12,40,0,0);
  wmove(vin, 0, 5);
  wbkgd(vin, COLOR_PAIR(1));
  
  while(ch != 1) {

    cur_pos = get_new_position(cur_pos, getch());
    vin=newwin(X_MAX,Y_MAX,0,0);
    draw_coords(vin, cur_pos, COORD_X, COORD_Y);
    wmove(vin, cur_pos.y, cur_pos.x);
    wbkgd(vin, COLOR_PAIR(1));
    wrefresh(vin);
  }
  delwin(vin);
  endwin();
}