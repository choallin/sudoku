// Here we have all implementation dependencies
#include <stdio.h>   /* Standard IO functions */
#include <stdlib.h>  /* Standard stdlib (system) functions */
#include <string.h>  /* String library, might be useful */

#include "../lib/terminal_view.h"

// Declaration of function which are "private"
void update_view(const void *self, Sudoku *data_source, int mode);
void redraw_terminal();
void draw_edit_menu();
void draw_main_menu();
void draw_sudoku(Sudoku *sudoku);

// Implementation
struct TerminalView *newTerminalView() {
  // Allocate memory from heap so we can return a
  // pointer to the struct
  struct TerminalView *self = (struct TerminalView *)malloc(sizeof(struct TerminalView));

  if (self == NULL) {
    return NULL;
  }

  self->update_view = &update_view;
}

void update_view(const void *self, Sudoku *data_source, int mode) {
  redraw_terminal();
  draw_sudoku(data_source);

  if (mode == EDIT_MODE) {
    draw_edit_menu();
  }

  draw_main_menu();
}

void redraw_terminal() {
  system("clear");
}

void draw_edit_menu() {
  puts("====================================");
  puts("\t1. Next Column (nc)");
  puts("\t2. Previous Column (pc)");
  puts("\t2. Next Row (nr)");
  puts("\t2. Previous Row (pr)");
  puts("\t3. Put Digit (1-9)");
  puts("\t4. Remove Digit (0)");
  puts("");
}

void draw_main_menu() {
  puts("------------------------------------");
  puts("\t1. New Sudoku (n)");
  puts("\t2. Edit Sudoku (e)");
  puts("\t3. Solve Sudoku (s)");
  puts("\t4. Exit (q)");
  puts("");
}

void draw_sudoku(Sudoku *sudoku) {
  puts("             SUDOKU SOLVER");
  puts("             =============");
  puts("\v");

  puts("+===+===+====+====+===+====+====+===+===+");
  int row_counter = 0;
  for(int i = 1; i < 13; i++)
  {
    if ((i % 4) == 0) {
      puts("+===+===+====#====+===+====#====+===+===+");
    } else {
      row_counter ++;
      char *row;
      row = sudoku->get_row(sudoku, row_counter);
      // We know that a row consist of 9 elements, so we can
      // access them as if they were an array
      printf("| %c | %c | %c  #  %c | %c | %c  #  %c | %c | %c |\n",
        row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8]);
    }

  }
  puts("");
}


