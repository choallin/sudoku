#ifndef SIMPLE_TERMINAM_DRAWER
#define SIMPLE_TERMINAM_DRAWER

// Internal dependencies
#include "../lib/sudoku.h"

// This file defines the public interface
// to the terminal presenter
// (datastructures + methods)

#define EDIT_MODE 1

// Here the struct is used as kind of a
// namespace and for easier polymorphism
// if needed
struct TerminalView
{
  void (*update_view)(const void *self, Sudoku *data_source, int mode);
};

struct TerminalView *newTerminalView();


#endif // SIMPLE_TERMINAM_DRAWER
