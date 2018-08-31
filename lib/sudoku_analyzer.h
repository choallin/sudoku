#if !defined(SUDOKU_ANALYZER)
#define SUDOKU_ANALYZER

#include "../lib/sudoku.h"

typedef struct SudokuAnalyzer {
  // Here we define a function pointer to get a
  // prototype like object orientation
  int (*analyze_sudoku)(const void *self, Sudoku *sudoku);
} SudokuAnalyzer;

SudokuAnalyzer *newSudokuAnalyzer();

#endif //SUDOKU_ANALYZER
