#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFLENGTH 10000

/* typedefs */
typedef int File;

typedef struct {
  int len;
  char *contents;
} Buffer;

typedef struct {
  File file;
  int pos;
  int len;
  void *prev;
  void *next;
} Piece;

typedef struct {
  Piece *contents;
} Piece_list;

typedef struct {
  int len;
  char *name;
  Piece contents[];
} Text;

typedef struct {
  int col;
  int line;
} Coordinates;

/* for highlights ({0,0} if none) */
typedef struct {
  int beg;
  int end;
} Selection;

/* for frame */
typedef struct {
  Text *text;
  Coordinates cursor;
  int status;
  int height;
  int width;
  Selection selection; 
} Frame;

/* file operations */
int f_read(File, int, int);
int f_write(Text *, char *, int, int);
int f_open(char *, int);
int f_load(Text *, File, int, int);

/* piece operations */
Piece p_create(File, int, int);

void t_read_full(Text *);

/* edit operations */
void e_delete(Text, int, int);
void e_insert(Text, int, char *);
void e_append(Text *, Piece);

int 
f_read(File file, int pos, int len)
{
  char buf[BUFLENGTH];
  lseek(file, pos, SEEK_SET);
  read(file, buf, len);
  write(1, buf, len); 
  return 0;
}

int
f_write(Text *t, char *name, int pos, int len)
{
  File file;
  if ((file = open(name, O_WRONLY, 0)) == -1) {
    /* error in opening */ 
    return 1;
  } else {
    write(file, t->contents, len);
    close(file);
    return 0;
  }
}

File
f_open(char *name, int mode)
{
  return (File)open(name, mode, 0);
}

int 
f_load(Text *t, File file, int pos, int len)
{
  Piece p = p_create(file, pos, len);
  t->contents[0] = p;
  t->len = 1;
}

Piece
p_create(File file, int pos, int len)
{
  return (Piece){
    .file = file,
    .pos = pos,
    .len = len
  };
}

void
t_read_full(Text *t)
{
  /* this isn't how to actually read */
  /* this is just so I have output */
  Piece *p;
  int i = 0, 
      len = t->len;
  while (i < len) {
    printf("first%d\n", i);
    getchar();
    p = &t->contents[i];
    f_read(p->file, p->pos, p->len);
    i++;
    printf("secdon%d\n", i);
    getchar();
  }
}

void
e_append(Text *t, Piece p)
{
  t->contents[t->len] = p;
  int i = t->len;
}

int
main(int argc, char *argv[])
{
	Text t;
  t.len = 0;
  File file;
  Piece p = {
    .file = file,
    .pos = 3,
    .len = 2
  };
  
  if ((file = f_open("hello.txt", O_RDONLY)) == -1) {
    return 1;
  } else {
    t.name = "hello.txt";
  }

  f_load(&t, file, 4, 3);
  e_append(&t, p);
  
  t_read_full(&t);
  
  return 0;
}
