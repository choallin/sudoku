#include <stdio.h>   /* Standard IO functions */
#include <stdlib.h>  /* Standard stdlib (system) functions */
#include <string.h>  /* String library, might be useful */

#include "../lib/simple_terminal_drawer.h"
#include "../lib/sudoku.h"

void initial_terminal_setup() {
  system("clear");
}

void create_main_menu() {
  puts("\t\tSUDOKU SOLVER");
  puts("\t\t=============");
  puts("\v");
  draw_sudoku();
  puts("");
  puts("------------------------------------");
  puts("\t1. New Sudoku (n)");
  puts("\t2. Edit Sudoku (e)");
  puts("\t3. Solve Sudoku (s)");
  puts("\t4. Exit (q)");
  puts("");
}

void draw_sudoku() {
  puts("+===+===+===+===+===+===+===+===+===+");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  puts("+===+===+===#===+===+===#===+===+===+");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  puts("+===+===+===#===+===+===#===+===+===+");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  printf("|---|---|---#---|---|---#---|---|---|\n");
  puts("+===+===+===+===+===+===+===+===+===+");
}


