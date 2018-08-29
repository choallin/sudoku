// Here we have all implementation dependencies
#include <stdio.h>   /* Standard IO functions */
#include <stdlib.h>  /* Standard stdlib (system) functions */
#include <string.h>  /* String library, might be useful */

#include "../lib/terminal_view.h"

// Declaration of function which are "private"
void update_view(const void *self, Sudoku *data_source, int mode);
void redraw_terminal();
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
  draw_main_menu();
}

void redraw_terminal() {
  system("clear");
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
  // uint8_t *row;
  // row = sudoku->get_row(sudoku, 1);

  puts("+===+===+===+===+===+===+===+===+===+");
  for(int i = 1; i < 13; i++)
  {
    if ((i % 4) == 0) {
      puts("+===+===+===#===+===+===#===+===+===+");
    } else {
      printf("|---|---|---#---|---|---#---|---|---|\n");
    }

  }
  puts("");
}


