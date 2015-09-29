#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
  int file;
  int pos;
  int len;
  void *prev;
  void *next;
} Piece;

typedef struct {
  int len;
  char *name;
  Piece contents[8];
} Text;

void
stream_to_stdout(int fd, int pos, int len)
{
  char buf[100];
  lseek(fd, pos, SEEK_SET);
  read(fd, buf, len);
  write(1, buf, len);
}

void
print_table(Text t)
{
  int i = 0;
  int len = t.len;
  for (; i < len; i++) {
    printf("AOEAOUE\n");
    printf("fd: %d\n", t.contents[i].file);
    /*stream_to_stdout(
      t.contents[i].file, 
      t.contents[i].pos, 
      t.contents[i].len
    ); */
  }
}

int
main(int argc, char *argv[])
{
  int f1, f2, f3;
  f1 = open("hello.txt", O_RDONLY, 0);
  printf("f1 = %d\n", f1);
  f2 = open("hello1.txt", O_RDONLY, 0);
  printf("f2 = %d\n", f2);
  f3 = open("hello2.txt", O_RDONLY, 0);
  printf("f3 = %d\n", f3);
  write(1, "HEAHUOEUH", 0);
  Piece p1 = {
    .file = f1,
    .pos = 1,
    .len = 2
  }; 
  Piece p2 = {
    .file = f2,
    .pos = 3,
    .len = 1
  }; 
  Piece p3 = {
    .file = f3,
    .pos = 1,
    .len = 4
  }; 
  Text *t = malloc(sizeof(Text));
  t->len = 3;
  t->name = "hellos";
  t->contents[0] = p1;
  t->contents[1] = p2;
  t->contents[2] = p3;
  print_table(*t);
}
