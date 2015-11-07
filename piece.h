#include "file.h"

typedef struct piece_descriptor {
  File file; 
  int start;
  int length;
  struct piece_descriptor *prev;
  struct piece_descriptor *next;
} Piece_Descriptor

typedef Piece_Descriptor *Piece;
