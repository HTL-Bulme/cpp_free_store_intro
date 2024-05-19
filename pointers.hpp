#ifndef POINTERS_HPP
#define POINTERS_HPP

#include <cstddef>

//! Swap the value of `a` and `b`.
void swap(int* a, int* b);

//! Reverses a given array in-place
void reverse(int* array, std::size_t count);

//! Return a pointer to the first element matching the value of `needle`.
//! If there are no matches, return `nullptr`.
int* find(int needle, int* haystack, std::size_t count);

//! Return a pointer to the first row containing the value of `needle`.
//! If there are no matches, return `nullptr`.
int* find_containing_row(int needle, int** matrix,
                         std::size_t rows, std::size_t cols);

#endif  // POINTERS_HPP
