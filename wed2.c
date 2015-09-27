#include <stdio.h>
#include <curses.h>

#define WINDOW_WIDTH 40
#define WINDOW_HEIGHT 12

typedef struct {
  int col;
  int line;
} Position;

static Position cur_pos;

int l_keypress(void);
void get_key_press(void);
void draw_screen(WINDOW *);
void l_redraw_screen(WINDOW *);
void kill_screen(WINDOW *);

int
l_keypress(void)
{
  int ch;
  ch = getch();

  /*
   * manage keypresses here
   */
 
  return ch;
}

void
draw_screen(WINDOW *win)
{
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  win = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0);
  wmove(win, 0, 5);
  wbkgd(win, COLOR_PAIR(1));
}

void
l_redraw_screen(WINDOW *win)
{
  win = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0);
  wbkgd(win, COLOR_PAIR(1));
  wrefresh(win);
}

void
kill_screen(WINDOW *win)
{
  delwin(win);
  endwin();
}

int
main(void)
{
  WINDOW *win;
  int ch;
 
  keypad(stdscr, TRUE); 
  noecho();
  draw_screen(win); 
  while (ch != 49) {
    ch = l_keypress();
    l_redraw_screen(win); 
  }
  
  kill_screen(win);
  return 0;
}
