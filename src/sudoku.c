#include <stdlib.h>  /* Standard stdlib (system) functions */
#include <stdio.h>   /* Standard IO functions */

#include "../lib/sudoku.h"

Sudoku *newSudoku() {
  // Allocate memory from heap so we can return a
  // pointer to the struct
  // IMPORTANT: The user of this "object" has to
  // make sure to free the memory when it is not needed
  // anymore
  printf("allocate memory: %ld \n", sizeof(Sudoku));
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
  self->_values[81];
  return self;
}

uint8_t *get_row(const void *self,int row_number) {

}

uint8_t *get_column(const void *self,int column_number) {

}

void set_value(const void *self, int row, int column, uint8_t value) {

}
