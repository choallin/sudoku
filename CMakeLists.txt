cmake_minimum_required(VERSION 3.12)
project(sudoku C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(lib)
include_directories(src)

add_executable(sudoku
        lib/input_manager.h
        lib/sudoku.h
        lib/sudoku_analyzer.h
        lib/terminal_view.h
        src/input_manager.c
        src/sudoku.c
        src/sudoku_analyzer.c
        src/terminal_view.c
        main.c)
