// #include <stdbool.h> /* true false definition */
#include <stdio.h>   /* Standard IO functions */
#include <string.h>  /* String library, might be useful */
#include <stdint.h> /* int size definition */
#include <stdlib.h>  /* Standard stdlib (system) functions */

#include "lib/terminal_view.h"
#include "lib/sudoku.h"
#include "lib/sudoku_analyzer.h"
#include "lib/input_manager.h"


void initialize_new_sudoku(Sudoku *sudoku) {
  // We free the memory of the old Sudoku
  free(sudoku);
  // And create a new one.
  // Performance can be improved since we allocate
  // memory again but for this small programm it will
  // work
  sudoku = newSudoku();
  sudoku->set_column(sudoku, 0, 'X');
  char tmp[82] = {
    '2','X','4','-','-','8','-','-','7',
    '-','-','7','3','2','-','-','-','-',
    '9','-','8','-','7','-','6','-','-',
    '-','-','3','6','1','-','-','7','-',
    '7','1','-','-','-','-','-','4','6',
    '-','4','-','-','5','2','3','-','-',
    '-','-','2','-','6','-','9','-','3',
    '-','-','-','-','4','3','7','-','-',
    '3','-','-','2','-','-','4','-','5',
    '\0'
  } ;

  for(int i = 0; i < 82; i++)
  {
    sudoku->set_column(sudoku, i, tmp[i]);
  }
}

int main(int argc, char const *argv[])
{
  char *menu_selection;
  Sudoku *current_sudoku;
  current_sudoku = newSudoku();
  initialize_new_sudoku(current_sudoku);

  // Initialize a SudokuAnalzer
  SudokuAnalyzer *sudoku_analyzer;
  sudoku_analyzer = newSudokuAnalyzer();

  // Create the view manager
  struct TerminalView *view = newTerminalView();
  // The view manager is also able to create an
  // empty Sudoku, so here we initialize it
  view->update_view(view, current_sudoku, EDIT_MODE);

  // Setup the input handling
  struct InputManager *input = newInputManager();

  int input_switch;
  int last_mode = EDIT_MODE;
  do
  {
    // Waiting for input to see what we should do next
    puts("Please choose... ");
    input_switch = input->process_input(input, current_sudoku);
    switch (input_switch)
    {
      case NEW_SUDOKU:
        // Since the new and edit action draws
        // exactly the same thing we don't need
        // a break in this case statement
        initialize_new_sudoku(current_sudoku);
      case EDIT_SUDOKU:
        view->update_view(view, current_sudoku, EDIT_MODE);
        last_mode = EDIT_MODE;
        break;
      case SOLVE_SUDOKU:
        // Again after solving the sudoku, we want
        // to update the view again, so we let it fall
        // through
        sudoku_analyzer->analyze_sudoku(sudoku_analyzer, current_sudoku);
      default:
        view->update_view(view, current_sudoku, last_mode);
        break;
    }
  } while (input_switch != QUIT );
  return 0;
}
