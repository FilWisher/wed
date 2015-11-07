#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* open_file */
int f_open_read(char *name, File *f)
{
  if ((f->fd = open(name, O_RDONLY)) < 0) {
    perror("open_file_read"); 
    return 0;
  }
  return 1;
}

int f_open_write(char *name, File *f)
{
  if ((f->fd = open(name, O_WRONLY | O_CREAT)) < 0) {
    perror("open_file_write"); 
    return 0;
  }
  return 1;
}

/* close_file */
int f_close(File *f) {
  close(f->fd);
}

/* read_file */
int f_read(File *f, int dst, int start, int len)
{
  if (len > MAX_BUF) {
    perror("len > MAX_BUF");
    return 0; 
  }
  char buf[MAX_BUF];
  lseek(f->fd, start, SEEK_SET);
  if (read(f->fd, buf, len) < 0) {
    perror("read_file: read");
    return 0; 
  }
  if (write(dst, buf, strlen(buf)) < 0) {
    perror("read_file: write");
    return 0; 
  }
  return 1;
}
