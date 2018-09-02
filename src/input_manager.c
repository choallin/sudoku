
// Development dependencies
#include <stdio.h>   /* Standard IO functions */
#include <string.h>  /* String library, might be useful */
#include <stdlib.h>  /* Standard stdlib (system) functions */

#include "../lib/input_manager.h"

int process_input(void *self, Sudoku *model);
int convert_to_menu_enum(char *menu_selection);
// Mutliplicator is the 2nd return value
int convert_to_consts(char *input, int *multiplicator);
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
  int *multiplicator;
  *multiplicator = 0;
  current_col = current_column(model);
  int switch_const = convert_to_consts(input, multiplicator);
  switch (switch_const)
  {
    case NEXT_COLUMN:
      puts("move in grid");
      *multiplicator = (*multiplicator > 0) ? *multiplicator : 1;
      printf("multplicator; %d", multiplicator);
      move_on_model(converted_self, model, current_col, *multiplicator, 'X');
      menu_state = EDIT_SUDOKU;
      break;
    case PREVIOUS_COLUMN:
      *multiplicator = (*multiplicator > 0) ? *multiplicator : 1;
      move_on_model(converted_self, model, current_col, *multiplicator * (-1), 'X');
      menu_state = EDIT_SUDOKU;
      break;
    case NEXT_ROW:
      *multiplicator = (*multiplicator > 0) ? *multiplicator : 1;
      move_on_model(converted_self, model, current_col, *multiplicator * 9, 'X');
      // With the state EDIT_SUDOKU we can redraw the output
      menu_state = EDIT_SUDOKU;
      break;
    case PREVIOUS_ROW:
      // If we move over a column we need to cache the old
      // value of it so we can put it in again
      *multiplicator = (*multiplicator > 0) ? *multiplicator : 1;
      move_on_model(converted_self, model, current_col, *multiplicator * (-9), 'X');
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

int convert_to_consts(char *input, int *multiplicator) {
  // Only valid mulitplicators are 1-9 so we check if the
  // first char is in this range and that the max length
  // is equal 3 (all navigation commands a 2 char commands)
  if (strchr("123456789", input[0]) && strlen(input) == 3) {
    *multiplicator = atoi(input);
    // Here we remove the first element of the input
    // by moving the pointer to the first element of
    // the input to the 2nd actual element.
    input = &input[1];

    // If the strlen is still bigger than 2 there is an invalid
    // input so we do nothing
    if (strlen(input) > 2) {
      return DO_NOTHING;
    }

  }
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
  int digit = atoi(input);
  // When the user wants to put a number in a col
  // that is not between 1 - 9 we do nothing
  if (digit < 1 || digit > 9) {
    return DO_NOTHING;
  }
  return digit;
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
}
