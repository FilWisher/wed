/*
 * TODO: Read/write files (and wtf is fflush)
 * TODO: Define key bindings in config.h
 * TODO: Define movement and edit functions
 * TODO: Check keypresses against keybindings
 * TODO: Draw text buffer into screen
 * TODO: Edit buffer via pointer to text[]
 * TODO: Write unit tests to check functionality
 */

#include <stdio.h>
#include <curses.h>

#define WINDOW_WIDTH 40
#define WINDOW_HEIGHT 12

/* typedefs */
typedef struct {
  int col;
  int line;
} Position;

static Position cur_pos; /* cursor position */

size_t size_of_string(char *);
int l_keypress(void);
void get_key_press(void);
void draw_screen(WINDOW *);
void l_redraw_screen(WINDOW *);
void kill_screen(WINDOW *);

size_t
size_of_string(char *string)
{
  int size = 0;
  while(*(string+size) != '\0')
    size++;
  return (size_t)size;
}

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
  wmove(win, cur_pos.line, cur_pos.col);
  wbkgd(win, COLOR_PAIR(1));
}

void
l_redraw_screen(WINDOW *win)
{
  win = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0);
  wmove(win, cur_pos.line, cur_pos.col);
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

  cur_pos.line = 2;
  cur_pos.col = 2;
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
