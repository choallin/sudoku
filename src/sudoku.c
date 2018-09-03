#include <stdlib.h>  /* Standard stdlib functions */
#include <string.h>  /* String library, might be useful */
#include <stdio.h>   /* Standard IO functions */

// include all internal dependencies
#include "../lib/sudoku.h"

#define ALLOWED_CHARS "123456789X-"

void set_column(void *self, int column, char value);
char *get_row(const void *self,int row_number);
char *get_row_for_column(const void *self, int column_number);
char get_column(const void *self,int column_number);
char *get_columns_for_column(const void *self, int field_index);
char *get_square_for_column(const void *self, int field_index);
void set_value(void *self, int row, int column, char value);

// Helper functions that are not bound to the object
int get_row_number(int column_number);
int get_column_index(int field_index);

Sudoku *newSudoku() {
  // Allocate memory from heap so we can return a
  // pointer to the struct
  // IMPORTANT: The user of this "object" has to
  // make sure to free the memory when it is not needed
  // anymore
  Sudoku *self = (Sudoku *)malloc(sizeof(Sudoku));

  // If we fail to allocate memory propagate failure with
  // returning NULL
  if (self == NULL) {
    return NULL;
  }

  // Set the function pointers to the right function
  // so that we have oo like behavior (& is not needed
  // but it makes the intention very clear)
  self->get_row = &get_row;
  self->get_row_for_column = &get_row_for_column;
  self->get_column = &get_column;
  self->set_value = &set_value;
  self->set_column = &set_column;
  self->get_columns_for_column = &get_columns_for_column;
  self->get_square_for_column = &get_square_for_column;

  // The values are initialized with '-' as default
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
  // this way we don't have to care about freeing memory
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

char *get_row_for_column(const void *self, int column_number) {
  Sudoku *converted_self = (Sudoku *)self;
  // We calculate the row number by subtracting 9 to the column_number
  // until we reach the first row i.e. until the result is < 10

  int row_number = get_row_number(column_number);
  return converted_self->get_row(self, row_number);
}

char get_column(const void *self, int column) {
  if (column < 0 || column > 81) {
    return '-';
  }
  Sudoku *converted_self = (Sudoku *)self;
  return converted_self->_values[column];
}

int get_row_number(int column_number) {
  int row = 1;
  if (column_number < 9) {
    return row;
  }
  while(column_number - (row * 9) >= 0){
    row++;
  }
  return row;
}

int get_column_index(int field_index) {
  int row_number = get_row_number(field_index);
  // We can calculate the column number by subtracting 9 times the
  // row - 1.
  int column_index;
  return (field_index - ((row_number - 1) * 9) + 1);
}

char *get_columns_for_column(const void *self, int field_index) {
  Sudoku *converted_self = (Sudoku *)self;
  static char column_digits[10];


  int column_index = get_column_index(field_index);
  // Now we put each char in column_digits
  for (int i = 0; i < 9; i++) {
    column_digits[i] = converted_self->_values[column_index - 1 + (i*9)];
  }
  column_digits[9] = '\0';
  return column_digits;
}

char *get_square_for_column(const void *self, int field_index) {
  Sudoku *converted_self = (Sudoku *)self;
  static char square_digits[10];

  int row_number = get_row_number(field_index) - 1;
  int column_index = get_column_index(field_index) - 1;

  int col_indizes[3];
  int row_indizes[3];

  switch (column_index % 3)
  {
    case 0:
      // The field is in the last column of the square we are looking for
      col_indizes[0] = column_index;
      col_indizes[1] = column_index + 1;
      col_indizes[2] = column_index + 2;
      break;
    case 1:
      col_indizes[0] = column_index - 1;
      col_indizes[1] = column_index;
      col_indizes[2] = column_index + 1;
      break;
    case 2:
      col_indizes[0] = column_index - 2;
      col_indizes[1] = column_index - 1;
      col_indizes[2] = column_index;
      break;
    default:
      break;
  }


  switch (row_number % 3)
  {
    case 0:
      row_indizes[0] = row_number;
      row_indizes[1] = row_number + 1;
      row_indizes[2] = row_number + 2;
      break;
    case 1:
      row_indizes[0] = row_number - 1;
      row_indizes[1] = row_number;
      row_indizes[2] = row_number + 1;
      break;
    case 2:
      row_indizes[0] = row_number - 2;
      row_indizes[1] = row_number - 1;
      row_indizes[2] = row_number;
      break;
    default:
      break;
  }

  int counter = 0;
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      int field_idx = col_indizes[i] + ((row_indizes[j]) * 9);

      square_digits[counter] = converted_self->_values[field_idx];
      counter++;
    }

  }
  square_digits[9] = '\0';
  return square_digits;
}

void set_value(void *self, int row, int column, char value) {

}

void set_column(void *self, int column, char value) {
  Sudoku *converted_self = (Sudoku *)self;
  if (strchr(ALLOWED_CHARS, value) == NULL) {
    return;
  }
  if (column < 0 || column > 81) {
    column = 0;
  }
  converted_self->_values[column] = value;
}
