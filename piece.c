#include <stdlib.h>
#include "piece.h"

/* create_piece */
Piece
p_create(Piece next, Piece prev, File f, int start, int len)
{
  Piece = p_alloc();
  p->file = f;
  p->start = start;
  p->len = len;
  p->prev = prev;
  p->next = next;
  return Piece;
}

int
p_set_next(Piece p, Piece next)
{
  if (p == NULL) {
    return 0; 
  } else {
    p->next = next; 
    return 1;
  }
}

int
p_set_prev(Piece p, Piece prev)
{
  if (p == NULL) {
    return 0; 
  } else {
    p->prev = prev; 
    return 1;
  }
}

/* delete_piece */
int 
p_delete(Piece p)
{
  Piece temp;
  p_set_next(p->prev, p->next);
  p_set_prev(p->next, p->prev);
  p_free(p);  
}

void 
p_free(Piece p)
{
  free(p);
}

Piece 
p_alloc(void)
{
  return (Piece)malloc(sizeof(Piece_Descriptor));
}

/* write_piece */
int
p_write(Piece p, int dst)
{
  return read_file(p->file, dst, p->start, p->len);
}
