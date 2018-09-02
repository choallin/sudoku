  #include <stdlib.h>  /* Standard stdlib functions */
#include <string.h>  /* String library, might be useful */
#include <stdio.h>   /* Standard IO functions */

// include all internal dependencies
#include "../lib/sudoku_analyzer.h"

int analyze_sudoku(const void *self, Sudoku *sudoku);
void remove_from_options(char *options, char *already_in_use);
int set_column_if_options_array_has_only_one_digit(Sudoku *sudoku, int column, char *options);

SudokuAnalyzer *newSudokuAnalyzer() {
  SudokuAnalyzer *self = (SudokuAnalyzer *)malloc(sizeof(SudokuAnalyzer));
  // If we fail to allocate memory propagate failure with
  // returning NULL
  if (self == NULL) {
    return NULL;
  }

  // Set the function pointers to the right function
  // so that we have oo like behavior (& is not needed
  // but it makes the intention very clear)
  self->analyze_sudoku = &analyze_sudoku;
}

int analyze_sudoku(const void *self, Sudoku *sudoku) {
  for(int i = 1; i < 82; i++)
  {
    int success = 0;
    // All possible values of a column
    // This can be rewritten of course but this way
    // it makes the intention what this var is for
    // very clear in my opinion
    char options[10] = "123456789";
    char *chars_in_row;
    chars_in_row = sudoku->get_row_for_column(sudoku, i);
    printf("In field %d we have this chars in the row: %s\n", i,chars_in_row);
    printf("length der chars: %d\n", strlen(chars_in_row));
    printf("addresse des char pointers: %p\n", (void *)chars_in_row);
    // After receiving all chars from one row, we remove
    // those from the one we have in our options
    remove_from_options(options, chars_in_row);
    printf("After removing the occuring chars from the row we have this options: %s\n", i, chars_in_row);
    // If we have only one option left, we put it in our field
    success = set_column_if_options_array_has_only_one_digit(sudoku, i, options);

    if (!success) {
      char *chars_in_column;
      chars_in_column = sudoku->get_columns_for_column(sudoku, i);
      remove_from_options(options, chars_in_column);
      printf("After removing the occuring chars from the col we have this options: %s\n", i, chars_in_column);
      success = set_column_if_options_array_has_only_one_digit(sudoku, i, options);
    }
  }
}

void remove_from_options(char *options, char *already_in_use) {
  // We iterate over already_in_use to remove these from the options
  int length = strlen(already_in_use);
  for(int i = 0; i < length; i++)
  {
    printf("index: %d\n", i);
    char *used_digit = strchr(options, already_in_use[i]);
    if (used_digit != NULL) {
      printf("digit '%c' is already in use, so we can savely unset it on index %d\n", already_in_use[i], i);
      // if the digit is already in use, we remove it from the options
      *used_digit = '-';
    }
  }
}

int set_column_if_options_array_has_only_one_digit(Sudoku *sudoku, int column, char *options) {
  int amount_of_digits = 0;
  int index_of_digit;
  for(int i = 0; i < strlen(options); i++)
  {
    // Here we check if the current char is a digit
    if (strchr("123456789", options[i])) {
      // If so we add one to our counter
      amount_of_digits++;
      index_of_digit = i;
    }
    if (amount_of_digits > 1) {
      return 0;
    }
  }

  // Here we can be sure that the amount of digits
  // in our options is only 1. And since we counted
  // the index as well, we already know where it is
  // so we just set it in the column
  sudoku->set_column(sudoku, column - 1, options[index_of_digit]);
  return 1;
}
