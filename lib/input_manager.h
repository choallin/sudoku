#if !defined(INPUT_MANAGGER)
#define INPUT_MANAGGER

#include "../lib/sudoku.h"

#define BUFF_SIZE 10

// @todo: make enum out of this
#define DO_NOTHING 100
#define NEXT_COLUMN 200
#define PREVIOUS_COLUMN 300
#define REMOVE_DIGIT 400

// Menu states
#define NEW_SUDOKU 110
#define EDIT_SUDOKU 101
#define SOLVE_SUDOKU 115
#define QUIT 113


// void await_input(char *str, int buf_size, char *type);

struct InputManager
{
  int (*process_input)(void *self, Sudoku *model);
  char _old_value_of_column;
};

struct InputManager *newInputManager();

#endif // INPUT_MANAGGER

