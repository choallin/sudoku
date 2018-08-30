#if !defined(SUDOKU)
#define SUDOKU

#include <stdint.h>   /* Standard int functions/typedefs */

typedef struct SudokuStruct {

  // Here we define a function pointer to get a
  // prototype like object orientation
  char* (*get_row)(const void *self, int row_number);
  char (*get_column)(const void *self, int column);
  void (*set_value)(void *self, int row, int column, char value);
  void (*set_column)(void *self, int column, char value);
  // We save the values in a flat array
  // it is still easy accessable because
  // we use this formular: row * col = index
  // But still, this is private
  char _values[82]; /* We have 81 fields and we need one more for the '\0' */
} Sudoku;

Sudoku *newSudoku();

#endif // SUDOKU
