#include "piece.h"

typedef struct {
  char name[TEXT_NAME_LEN];
  Piece head;
  Piece tail;
} Text;

typedef struct {
  Piece piece;
  int offset;
} Location;
