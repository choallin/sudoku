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
  // We look at every field to find out what options we have for it
  for(int i = 0; i < 82; i++)
  {
    char options[10] = "123456789";
    char col = sudoku->get_column(sudoku, i);
    // If the field is filled we go on to the next one
    if (strchr(options, col)) {
      continue;
    }

    int success = 0;
    // All possible values of a row
    char *chars_in_row;
    chars_in_row = sudoku->get_row_for_column(sudoku, i);
    // After receiving all chars from one row, we remove
    // those from the one we have in our options
    remove_from_options(options, chars_in_row);
    // If we have only one option left, we put it in our field
    success = set_column_if_options_array_has_only_one_digit(sudoku, i, options);

    if (!success) {
      // If we have more than one option left we continue with the column
      char *chars_in_column;
      chars_in_column = sudoku->get_columns_for_column(sudoku, i);
      remove_from_options(options, chars_in_column);
      success = set_column_if_options_array_has_only_one_digit(sudoku, i, options);
    }

    if (!success) {
      // look at the current square
      char *chars_in_square;
      chars_in_square = sudoku->get_square_for_column(sudoku, i);
      remove_from_options(options, chars_in_square);
      success = set_column_if_options_array_has_only_one_digit(sudoku, i, options);
    }
  }
}

void remove_from_options(char *options, char *already_in_use) {
  // We iterate over already_in_use to remove these from the options
  int length = strlen(already_in_use);
  for(int i = 0; i < length; i++)
  {
    char *used_digit = strchr(options, already_in_use[i]);
    if (used_digit != NULL) {
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

  if (index_of_digit > 81 || index_of_digit < 0) {
    return 0;
  }

  // Here we can be sure that the amount of digits
  // in our options is only 1. And since we counted
  // the index as well, we already know where it is
  // so we just set it in the column
  sudoku->set_column(sudoku, column, options[index_of_digit]);
  return 1;
}
