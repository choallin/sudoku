#include <stdlib.h>  /* Standard stdlib functions */
#include <string.h>  /* String library, might be useful */
#include <stdio.h>   /* Standard IO functions */

// include all internal dependencies
#include "../lib/sudoku.h"

Sudoku *newSudoku() {
  // Allocate memory from heap so we can return a
  // pointer to the struct
  // IMPORTANT: The user of this "object" has to
  // make sure to free the memory when it is not needed
  // anymore
  Sudoku *self = (Sudoku *)malloc(sizeof(Sudoku));

  // If we fail to allocate memory propage failure with
  // returning NULL
  if (self == NULL) {
    return NULL;
  }

  // Set the function pointers to the right function
  // so that we have oo like behavior (& is not needed
  // but it makes the intention very clear)
  self->get_row = &get_row;
  self->get_column = &get_column;
  self->set_value = &set_value;

  // The values are initialized with 0 as default

  for(int i = 0; i < 81; i++)
  {
    self->_values[i] = '-';
  }
  self->_values[81] = '\0';

  return self;
}

char *get_row(const void *self,int row_number) {
  Sudoku *converted_self = (Sudoku *)self;
  // Here we are using this static char array because
  // this way we don't have to care about the memory
  static char row_digits[10];
  // To find the index of the last element we look
  // at the grid and see that the last element is like
  // this: 9, 18, 27, 36, 45, ...
  // So, the formula would be: row_number * 10 - row_number
  // The last - 1 is there because the array starts
  // with 0, as it should be!
  int end_value = (row_number * 10 - row_number) - 1;
  // A row consists of 9 digits, so to find the first,
  // starting from the last, we have to subtract 8
  int start_value = end_value - 8;

  int counter = 0;
  for(int i = start_value; i <= end_value; i++)
  {
    row_digits[counter] = converted_self->_values[i];
    counter++;
  }
  return row_digits;
}

char *get_column(const void *self,int column_number) {

}

void set_value(void *self, int row, int column, char value) {

}
