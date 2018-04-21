cmake_minimum_required(VERSION 3.8)
project(sudoku)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/solver.h)
add_executable(sudoku ${SOURCE_FILES})