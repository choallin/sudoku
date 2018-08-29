// #include <stdbool.h> /* true false definition */
#include <stdio.h>   /* Standard IO functions */
#include <string.h>  /* String library, might be useful */
#include <stdint.h> /* int size definition */
#include <stdlib.h>  /* Standard stdlib (system) functions */

#include "lib/terminal_view.h"
#include "lib/sudoku.h"
#include "lib/helpers.h"

#define MENU_SIZE 10

#define NEW_SUDOKU 110
#define EDIT_SUDOKU 101
#define SOLVE_SUDOKU 115
#define QUIT 113


int convert_to_menu_enum(char *menu_selection) {
  return (int)menu_selection[0];
}

void initialize_new_sudoku(Sudoku *sudoku) {
  // We free the memory of the old Sudoku
  free(sudoku);
  // And create a new one.
  // Performance can be improved since we allocate
  // memory again but for this small programm it will
  // work
  sudoku = newSudoku();
}

int main(int argc, char const *argv[])
{
  char menu_selection[MENU_SIZE];
  Sudoku *current_sudoku;
  current_sudoku = newSudoku();
  // Create the view manager
  struct TerminalView *view = newTerminalView();
  // The view manager is also able to create an
  // empty Sudoku, so here we initialize it
  view->update_view(view, current_sudoku, EDIT_MODE);

  int input_switch;
  do
  {
    // Waiting for input to see what we should do next
    puts("Please choose... ");
    await_input(menu_selection, MENU_SIZE, "%s");
    input_switch = convert_to_menu_enum(menu_selection);
    switch (input_switch)
    {
      case NEW_SUDOKU:
        // Since the new and edit action draws
        // exactly the same thing we don't need
        // a break in this case statement
        initialize_new_sudoku(current_sudoku);
      case EDIT_SUDOKU:
        view->update_view(view, current_sudoku, EDIT_MODE);
        break;
      case SOLVE_SUDOKU:
        puts("Not implemented yet");
        break;
      default:
        break;
    }
  } while (input_switch != QUIT );


  return 0;
}
