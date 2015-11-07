/* includes */
#include "file.h"
#include "piece.h"
#include "text.h"

int
main(int argc, char *argv[])
{
 
  File f;
  
  /* if file provided, load it (or create it) */
  if (argc > 1) {
    if (!f_open_read(argv[1], f)) {
      perror("f_open_read"); 
      exit(1);
    }
  }

  /* execute edit_loop 
      - check if command received
      - execute command
      - send updated text to response
  */ 

  if (!f_read(f, 1, 0, 10)) {
    perror("f_read");
    exit(1);
  }
  
  return 0;
  /* return status code */
}
