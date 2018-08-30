
// Development dependencies
#include <stdio.h>   /* Standard IO functions */
#include <string.h>  /* String library, might be useful */
#include <stdlib.h>  /* Standard stdlib (system) functions */

#include "../lib/input_manager.h"



int process_input(const void *self, Sudoku *model);
int convert_to_menu_enum(char *menu_selection);
int convert_to_consts(char *input);
char *process_raw_input();
int current_column(Sudoku *model);

struct InputManager *newInputManager() {
  // Again we are using static because this is a "Singleton"
  struct InputManager *self = (struct InputManager *)malloc(sizeof(struct InputManager));
  if (self == NULL) {
    return NULL;
  }
  self->process_input = &process_input;
};

int process_input(const void *self, Sudoku *model) {
  // Here we are using static vars because this function does not
  // need to work with several structs, i.e. we have something like
  // a singleton here
  static char *input;
  // InputManager *converted_self = (InputManager *)self;
  int menu_state = DO_NOTHING;

  input = process_raw_input();

  int current_col = 0;
  current_col = current_column(model);
  switch (convert_to_consts(input))
  {
    case NEXT_COLUMN:
      // @todo: replace with set(row, column, value)
      model->_values[current_col] = '-';
      model->_values[current_col + 1] = 'X';
      // With the state EDIT_SUDOKU we can redraw the output
      menu_state = EDIT_SUDOKU;
      break;
    case PREVIOUS_COLUMN:
      // @todo: replace with set(row, column, value)
      model->_values[current_col] = '-';
      model->_values[current_col - 1] = 'X';
      menu_state = EDIT_SUDOKU;
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      model->_values[current_col] = input[0];
      model->_values[current_col + 1] = 'X';
      menu_state = EDIT_SUDOKU;
      break;
    case REMOVE_DIGIT:
      model->_values[current_col] = '-';
      model->_values[current_col + 1] = 'X';
      menu_state = EDIT_SUDOKU;
      break;
      break;
    case NEW_SUDOKU:
      menu_state = EDIT_SUDOKU;
      break;
    case EDIT_SUDOKU:
      menu_state = EDIT_SUDOKU;
      break;
    case SOLVE_SUDOKU:
      menu_state = SOLVE_SUDOKU;
      break;
    case QUIT:
      menu_state = QUIT;
      break;
    default:
      menu_state = convert_to_menu_enum(input);
      break;
  }

  return menu_state;
}

char *process_raw_input() {
  // Here we are using static vars because this function does not
  // need to work with several structs, i.e. we have something like
  // a singleton here
  static char str[BUFF_SIZE];
  // We use the fegts + sscanf combination to avoid a
  // '\n' being in the stdin buffer and also more important
  // to avoid a buffer overflow
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%s", str);
  return str;
}

int convert_to_menu_enum(char *menu_selection) {
  if(strlen(menu_selection) > 1) {
    return DO_NOTHING;
  }
  return (int)menu_selection[0];
}

int convert_to_consts(char *input) {

  if (strcmp(input, "nc") == 0) {
    return NEXT_COLUMN;
  }
  if (strcmp(input, "pc") == 0) {
    return PREVIOUS_COLUMN;
  }
  if (strcmp(input, "0") == 0) {
    return REMOVE_DIGIT;
  }
  return atoi(input);
}

int current_column(Sudoku *model) {
  // In case that the size of the _values array changes
  // So the knowledge of the size is in one place only,
  // the header file
  int array_length = sizeof(model->_values) / sizeof(model->_values[0]);
  // The current column is the column that is a 'X'
  // So we iterate over it and return the index of it
  for(int i = 0; i < array_length; i++)
  {
    if (model->_values[i] == 'X') {
      return i;
    }
  }
  // Default is the first column
  return 0;
}
