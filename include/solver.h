//
// Backtracking of a 9x9 sudoku board.
// Created by Kasey Stowell.
// Some help taken from the pseudo code of this stanford powerpoint.
// https://see.stanford.edu/materials/icspacs106b/Lecture11.pdf
// help with 2 dimensional array passing by val from stackoverflow:
// https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
//

#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <cstdlib>
#include <iostream>

/// Check for an empty spot while incrementing x and y.
/// @tparam rows multidimensional array row size.
/// @tparam cols multidimensional array column size.
/// @param array multidimensional array being passed.
/// @param x incremental row x.
/// @param y incremental column y.
/// @return true if a x,y combination in the array contains the value 0 which represents empty.
template <size_t rows, size_t cols>
bool isEmpty(int (&array)[rows][cols], int &x, int &y) {
    for (x = 0; x < rows; x++) {
        for (y = 0; y < cols; y++) {
            if (array[x][y] == 0) {
                return true; // found an empty spot!
            }
        }
    }
    return false;
};

/// Check for similar values in the y axis of the multidimensional array.
/// @tparam rows multidimensional array row size.
/// @tparam cols multidimensional array column size.
/// @param array multidimensional array being passed.
/// @param y column being checked.
/// @param val number to be matched if existing.
/// @return true if there is a match with val in the y axis of the multidimensional array,
template <size_t rows, size_t cols>
bool inYAxis(int (&array)[rows][cols], int y, int val) {
    for (int x = 0; x < rows; x++) {
        if (array[x][y] == val) {
            return true; // found the value. time to increment it instead.
        }
    }
    return false;
};

/// Check for similar values in the x axis of the multidimensional array.
/// @tparam rows multidimensional array row size.
/// @tparam cols multidimensional array column size.
/// @param array multidimensional array being passed.
/// @param x row being checked.
/// @param val number to be matched if existing.
/// @return true if there is a match with val in the x axis of the multidimensional array.
template <size_t rows, size_t cols>
bool inXAxis(int (&array)[rows][cols], int x, int val) {
    for (int y = 0; y < rows; y++) {
        if (array[x][y] == val) {
            return true; // found the value. time to increment it instead.
        }
    }
    return false;
};

/// Check for similar values in the mini multidimensional array.
/// @tparam rows multidimensional array row size.
/// @tparam cols multidimensional array column size.
/// @param array multidimensional array being passed.
/// @param x row being checked.
/// @param y column being checked.
/// @param val number to be matched if existing.
/// @return true if there is a match with val in the mini multidimensional array.
template <size_t rows, size_t cols>
bool inMini(int (&array)[rows][cols], int x, int y, int val) {
    // lets make sure we are starting in the correct box...
    int newx = x - (x % 3);
    int newy = y - (y % 3);
    // check the rows and columns of that small box.
    for (int minix = 0; minix < 3; minix++) {
        for (int miniy = 0; miniy < 3; miniy++) {
            if (array[minix + newx][miniy + newy] == val) {
                return true; // found the value. time to increment it instead.
            }
        }
    }
    return false;
};

/// Print the sudoku board.
/// @tparam rows multidimensional array row size.
/// @tparam cols multidimensional array column size.
/// @param array multidimensional array being passed.
template <size_t rows, size_t cols>
void print(int (&array)[rows][cols]) {
    for (int y = 0; y < cols * 2; y++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int x = 0; x < rows; x++) {
        std::cout << "|";
        for (int y = 0; y < cols; y++) {
            std::cout << array[x][y] << "|";
        }
        std::cout << std::endl;
    }
    for (int y = 0; y < cols * 2; y++) {
        std::cout << "-";
    }
    std::cout << std::endl;
};

/// Solve a sudoku problem.
/// @tparam rows multidimensional array row size.
/// @tparam cols multidimensional array column size.
/// @param array multidimensional array being passed.
/// @return true if solved.
template <size_t rows, size_t cols>
bool solve(int (&array)[rows][cols]) {
    int x, y;
    // if no more choices.. return.
    if (!isEmpty(array, x, y)) {
        return true;
    }
    // for all the numbers we can use (1-9)
    for (int val = 1; val < 10; val++) {
        // lets try the value!
        // check x, y, and mini square.
        if (!inYAxis(array, y, val) && !inXAxis(array, x, val) && !inMini(array, x, y, val)) {
            // looks like we have a spot!
            array[x][y] = val;
            // call yourself to see if we are done yet. sudoku is much more fun with recursion.
            if (solve(array)) {
                return true;
            }
            // looks like i gotta undo things and try over.
            array[x][y] = 0;
        }
    }
    return false; // no more possibilities. backtrack...
};

#endif //SUDOKU_SOLVER_H
