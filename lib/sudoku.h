#if !defined(SUDOKU)
#define SUDOKU

#include <stdint.h>   /* Standard int functions/typedefs */

typedef struct SudokuStruct {

  // Here we define a function pointer to get a
  // prototype like object orientation
  uint8_t* (*get_row)(const void *self, int row_number);
  uint8_t* (*get_column)(const void *self, int column_number);
  void (*set_value)(const void *self, int row, int column, uint8_t value);
  // We save the values in a flat array
  // it is still easy accessable because
  // we use this formular: row * col = index
  // But still, this is private
  uint8_t _values[81];
} Sudoku;

uint8_t *get_row(const void *self,int row_number);
uint8_t *get_column(const void *self,int column_number);
void set_value(const void *self, int row, int column, uint8_t value);
Sudoku *newSudoku();

#endif // SUDOKU
