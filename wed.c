/*
 * TODO: Define edit functions
 * TODO: Edit buffer via pointer to text[]
 * TODO: Write unit tests to check functionality
 * TODO: Check movement boundaries
 * TODO: Key combinations
 * TODO: Letter input default in insert mode
 */
 
/* INCLUDES */
#include <curses.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MACROS */
#define LEFT(POS, N) (Position){ POS.col - N, POS.line }
#define RIGHT(POS, N) (Position){ POS.col + N, POS.line }
#define UP(POS, N) (Position){ POS.col, POS.line - N }
#define DOWN(POS, N) (Position){ POS.col, POS.line + N }

#define WINDOW_WIDTH 40
#define WINDOW_HEIGHT 12
#define BUFSIZE 10000
#define COMMAND_MODE "command"
#define EDIT_MODE "edit"

/* TYPEDEFS */
typedef struct {
  int col;
  int line;
} Position;

typedef union {
  Position (*pos)(Position);
	char *val;
} Argument;

typedef struct {
  Position ruler_position;
	Position mode_position;
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

typedef struct {
	char *name;
	char *buf;
} File;

/* ENUMS */
enum {
	COMMAND, EDIT, FINAL
};

/* CONSTANTS */
static const char *modes[FINAL] = {
	"command",
	"edit"
};

/* VARIABLES */
static Position cur_pos = {0,0};
static char *editor_mode = COMMAND_MODE;
static Statusline status_bar = { 
  .ruler_position = { 
    .col = (WINDOW_WIDTH*2)/3,
    .line = WINDOW_HEIGHT-1
  },
	.mode_position = {
		.col = WINDOW_WIDTH/3,
		.line = WINDOW_HEIGHT-1
	}
};
static File file = { "-", "Welcome to Wed!" };

/** FUNCTIONS **/
/* k_* functions for keybinding functions */
void k_save(Argument *);
void k_move(Argument *);
void k_change_mode(Argument *);
void k_insert(Argument *);

/* l_* functions for loop functions */
int l_keypress(void);
void l_redraw_screen(WINDOW *);

/* f_* functions for file control */
void f_read_file(char *name);
void f_cleanup_file(void);

/* m_* movement functions */
Position m_left_one(Position);
Position m_right_one(Position);
Position m_up_one(Position);
Position m_down_one(Position);
Position m_noop(Position);

/* for keybindings */
#include "config.h"

Keyset *get_key_bindings(void);
size_t size_of_string(char *);
void draw_text(WINDOW *, char *);
void draw_status_bar(WINDOW *);
void draw_mode(WINDOW *win);
void draw_coords(WINDOW *);
void draw_screen(WINDOW *);
void kill_screen(WINDOW *);

Position m_left_one(Position pos) { return LEFT(pos, 1); }
Position m_right_one(Position pos) { return RIGHT(pos, 1); }
Position m_up_one(Position pos) { return UP(pos, 1); }
Position m_down_one(Position pos) { return DOWN(pos, 1); }
Position m_noop(Position pos) { return pos; }

void
k_save(Argument *arg)
{
	int fd;
  if((fd = open(file.name, O_WRONLY, 0)) == -1) {
		/* could not open file */	
	} else {
		write(fd, file.buf, BUFSIZE);		
	}
	close(fd);
}

void
k_insert(Argument *arg)
{
	strcat(file.buf, arg->val);
	cur_pos.col++;
}

void 
f_read_file(char *name)
{
	int fd;
	file.name = name;
	file.buf = (char *)malloc(BUFSIZE);
	if ((fd = open(name, O_RDONLY, 0)) == -1) {
		/* could not open file */	
	}	else {
		read(fd, file.buf, BUFSIZE);	
	}
	close(fd);
}

void
f_cleanup_file(void)
{
	free(file.buf);
}

size_t
size_of_string(char *string)
{
  int size = 0;
  while(*(string+size) != '\0')
    size++;
  return size * sizeof(char);
}

void
draw_text(WINDOW *win, char *text)
{
	int i;
	size_t text_length = strlen(text);
	wmove(win, 0, 0);
	for (i = 0; i < text_length; i++) {
		waddch(win, *(text+i));	
	}
}

void
draw_status_bar(WINDOW *win)
{
	draw_mode(win);
	draw_coords(win);
}

void
draw_mode(WINDOW *win)
{
	wmove(win, status_bar.mode_position.line, status_bar.mode_position.col);
	wprintw(win, editor_mode);
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

void
k_change_mode(Argument *arg)
{
	strcpy(editor_mode, arg->val);
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
	
	if (strcmp(editor_mode, "edit") == 0) {
		//key->func = k_insert;
		strncpy(key->arg.val, (char *)ch, sizeof(ch));
	}
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
	wrefresh(win);
}

void
l_redraw_screen(WINDOW *win)
{
  win = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0);
  draw_status_bar(win);
	draw_text(win, file.buf);
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
main(int argc, char *argv[])
{
  WINDOW *win;
  int ch;

	f_read_file(argv[1]);

  keypad(stdscr, TRUE); 
  noecho();
  draw_screen(win); 
  while (ch != 49) {
    l_redraw_screen(win); 
    ch = l_keypress();
  }
	f_cleanup_file();  
  kill_screen(win);
  return 0;
}
