// #include <stdbool.h> /* true false definition */
#include <stdio.h>   /* Standard IO functions */
#include <string.h>  /* String library, might be useful */
#include <stdint.h> /* int size definition */
#include <stdlib.h>  /* Standard stdlib (system) functions */

#include "lib/simple_terminal_drawer.h"
#include "lib/sudoku.h"

int main(int argc, char const *argv[])
{
  char menu_selection[2];
  initial_terminal_setup();
  create_main_menu();


  do
  {

  } while (!strcmp(menu_selection, "q") );


  return 0;
}
