
// Development dependencies
#include <stdio.h>   /* Standard IO functions */
#include <string.h>  /* String library, might be useful */
#include <stdlib.h>  /* Standard stdlib (system) functions */

#include "../lib/input_manager.h"

int process_input(void *self, Sudoku *model);
int convert_to_menu_enum(char *menu_selection);
int convert_to_consts(char *input);
char *process_raw_input();
int current_column(Sudoku *model);
void move_on_model(struct InputManager *self, Sudoku *model, int current_col, int distance, char value);

struct InputManager *newInputManager() {
  // Again we are using static because this is a "Singleton"
  struct InputManager *self = (struct InputManager *)malloc(sizeof(struct InputManager));
  if (self == NULL) {
    return NULL;
  }
  self->process_input = &process_input;
  self->_old_value_of_column = '-';
};

int process_input(void *self, Sudoku *model) {
  // Here we are using static vars because this function does not
  // need to work with several structs, i.e. we have something like
  // a singleton here
  static char *input;
  struct InputManager *converted_self = (struct InputManager *)self;
  int menu_state = DO_NOTHING;

  input = process_raw_input();

  int current_col = 0;
  current_col = current_column(model);
  switch (convert_to_consts(input))
  {
    case NEXT_COLUMN:
      move_on_model(converted_self, model, current_col, 1, 'X');
      menu_state = EDIT_SUDOKU;
      break;
    case PREVIOUS_COLUMN:
      move_on_model(converted_self, model, current_col, -1, 'X');
      menu_state = EDIT_SUDOKU;
      break;
    case NEXT_ROW:
      move_on_model(converted_self, model, current_col, 9, 'X');
      // With the state EDIT_SUDOKU we can redraw the output
      menu_state = EDIT_SUDOKU;
      break;
    case PREVIOUS_ROW:
      // If we move over a column we need to cache the old
      // value of it so we can put it in again
      move_on_model(converted_self, model, current_col, -9, 'X');
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
      // Erase cache
      converted_self->_old_value_of_column = '-';
      model->set_column(model, current_col, input[0]);
      model->set_column(model, current_col + 1, 'X');
      menu_state = EDIT_SUDOKU;
      break;
    case REMOVE_DIGIT:
      // Erase cache
      converted_self->_old_value_of_column = '-';
      model->set_column(model, current_col, '-');
      model->set_column(model, current_col + 1, 'X');
      menu_state = EDIT_SUDOKU;
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
  if (strcmp(input, "nr") == 0) {
    return NEXT_ROW;
  }
  if (strcmp(input, "pr") == 0) {
    return PREVIOUS_ROW;
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

void move_on_model(struct InputManager *self, Sudoku *model, int current_col, int distance, char value) {
  // If we move over a column we need to cache the old
  // value of it so we can put it in again
  model->set_column(model, current_col, self->_old_value_of_column);
  self->_old_value_of_column = model->get_column(model, current_col + distance);
  model->set_column(model, current_col + distance, value);
  // With the state EDIT_SUDOKU we can redraw the output
}
