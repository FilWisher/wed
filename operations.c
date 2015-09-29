#include <sys/stat.h>
#include <fcntl.h>

/* Text Manipulation */
/* for sections of text */
typedef struct {
  int len;
  char *contents;
} Buffer;

/* for internal version of text and name of file */
typedef struct {
  int len;
  char *contents;
  char *name;
} Text;

/* for file descriptor of file */
typedef int File;

/* Text Rendering */
/* for coordinates in frame */
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


