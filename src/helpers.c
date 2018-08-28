#include <stdio.h>   /* Standard IO functions */
#include <string.h>  /* String library, might be useful */

// @todo: rewrite with varargs so that this method would be
// more comfortable to use
void await_input(char *str, int buf_size, char *type) {
  char tmp[buf_size];
  // We use the fegts + sscanf combination to avoid a
  // '\n' being in the stdin buffer and also more important
  // to avoid a buffer overflow
  fgets(tmp, sizeof(tmp), stdin);
  sscanf(tmp, type, str);
}

