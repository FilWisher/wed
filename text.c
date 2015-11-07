#include <stdlib.h>
#include "text.h"

/* write_text */
int
t_write(const Text *t, int fd)
{
  if (!t) {
    return 0; 
  }
  Piece p = t->head;
  for (Piece p = t->head; p; p = p->next) {
    if (!p_write(p, fd)) {
      return 0; 
    }
  }
  return 1;
}

int
t_delete(Text *t)
{
  if (!t) {
    return 0; 
  }
  for (Piece p = t->head; p; p = p->next) {
    p_free(p); 
  }
  return 1;
}

/* pos_to_piece */
Location
t_pos_to_loc(const Text *t, int pos)
{
  Location l;
  l.piece = t->head;
  l.offset = pos; 
  while (l.piece && l.pos > l.piece->len) {
    l.pos -= l.piece->len;
    l.piece = l.piece->next;
  }
  return l; 
}
