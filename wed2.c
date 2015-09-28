/*
 * TODO: Read/write files (and wtf is fflush)
 * TODO: Define edit functions
 * TODO: Draw text buffer into screen
 * TODO: Edit buffer via pointer to text[]
 * TODO: Write unit tests to check functionality
 */
 
/* INCLUDES */
#include <stdio.h>
#include <string.h>
#include <curses.h>

/* INCLUDES (local) */

/* MACROS */
#define LEFT(POS, N) (Position){ POS.col - N, POS.line }
#define RIGHT(POS, N) (Position){ POS.col + N, POS.line }
#define UP(POS, N) (Position){ POS.col, POS.line - N }
#define DOWN(POS, N) (Position){ POS.col, POS.line + N }

#define WINDOW_WIDTH 40
#define WINDOW_HEIGHT 12

/* TYPEDEFS */
typedef struct {
  int col;
  int line;
} Position;

typedef union {
  Position (*pos)(Position);
} Argument;

typedef struct {
  Position ruler_position;
} Statusline;

typedef struct {
  union { 
    int c;
  } val;
  void (*func)(Argument *);
  Argument arg;
} Key;

typedef struct {
  char *mode;
  const Key *mode_keys;
} Keyset;

/* ENUMS */

/* CONSTANTS */

/* VARIABLES */
static Position cur_pos;
static char *editor_mode = "command"; 
static Statusline status_bar = { 
  .ruler_position = { 
    .col = (WINDOW_WIDTH*2)/3,
    .line = WINDOW_HEIGHT-1
  }
};

/** FUNCTIONS **/
/* k_* functions for keybinding functions */
void k_move(Argument *);

/* l_* functions for loop functions */
int l_keypress(void);
void l_redraw_screen(WINDOW *);
void draw_coords(WINDOW *);

/* m_* movement functions */
Position m_left_one(Position);
Position m_right_one(Position);
Position m_up_one(Position);
Position m_down_one(Position);
Position m_noop(Position);

/* for keybindings */
#include "config2.h"

Keyset *get_key_bindings(void);
size_t size_of_string(char *);
void draw_screen(WINDOW *);
void kill_screen(WINDOW *);

Position m_left_one(Position pos) { return LEFT(pos, 1); }
Position m_right_one(Position pos) { return RIGHT(pos, 1); }
Position m_up_one(Position pos) { return UP(pos, 1); }
Position m_down_one(Position pos) { return DOWN(pos, 1); }
Position m_noop(Position pos) { return pos; }

size_t
size_of_string(char *string)
{
  int size = 0;
  while(*(string+size) != '\0')
    size++;
  return size * sizeof(char);
}

void
draw_coords(WINDOW *win)
{
  char line_str[5], col_str[5], coord_str[10];
  snprintf(line_str, size_of_string(line_str), "%d", cur_pos.line);
  snprintf(col_str, size_of_string(col_str), "%d", cur_pos.col);
  strcpy(coord_str, line_str);
  strcat(coord_str, ",");
  strcat(coord_str, col_str);
  wmove(win, status_bar.ruler_position.line, status_bar.ruler_position.col);
  wprintw(win, coord_str);
}

void 
k_move(Argument *arg)
{
  cur_pos = arg->pos(cur_pos);
}

Keyset *
get_key_bindings(void)
{
  int i;
  int b_length = sizeof(bindings) / sizeof(Keyset);
  Keyset *binding = bindings;

  while(b_length--) {
    if (strcmp(editor_mode, binding->mode) != 0) {
      binding++;
    }
  }
  return binding;
}

int
l_keypress(void)
{
  int ch = getch(), i;
  Argument *arg;
 
  Keyset *binding = get_key_bindings();
  Key *key = binding->mode_keys;
  
  while (key->val.c != ch && key->val.c != '\0')
    key++; 

  key->func(&key->arg);
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
  draw_coords(win);
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
    l_redraw_screen(win); 
    ch = l_keypress();
  }
  
  kill_screen(win);
  return 0;
}
