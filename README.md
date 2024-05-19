# C++ Pointer Exercises

In this homework you are asked to restrict yourself to not using any
`include` except `<cstddef>`.
The purpose of is to understand and comfortable with pointers and hence
you'll have to juggle the data for yourself instead of including most of the
solutions.

Compile your code via

```shell
mkdir build -p && cd build
cmake ..
make -j8  # use 8 processor cores when compiling
```

If needed, consult the test files
([pointers_test.cpp](pointers_test.cpp),
 [matrix_test.cpp](matrix_test.cpp) and
 [sort_test.cpp](sort_test.cpp))
to understand what exactly your code needs to accomplish.


## Task 1 - Introductory Tasks
The following subtasks all have to be implemented in `pointers.cpp` and
the required functions and data structures declared in `pointers.hpp`.

### Swap the Value of two Variables
Implement a function to swap the value of two `int` variables.

```cpp
//! Swap the value of `a` and `b`.
void swap(int* a, int* b);
```

### Array Functions
Implement the follwoing functions:

```cpp
//! Reverses a given array in-place
void reverse(int* array, std::size_t count);

//! Return a pointer to the first element matching the value of `needle`.
//! If there are no matches, return `nullptr`.
int* find(int needle, int* haystack, std::size_t count);

//! Return a pointer to the first row containing the value of `needle`.
//! If there are no matches, return `nullptr`.
int* find_containing_row(int needle, int** matrix,
                         std::size_t rows, std::size_t cols);
```


## Task 2 - Matrices
A Matrix can be stored as an array of `row` arrays with `cols` elements in
each. Alternatively, a matrix can be represented as a single array containing
`row * cols` elements. It is your duty to find if a matrix given in the first
form is equivalent to a matrix given in the second form. The two
representations are equivalent if and only if all elements have the same value
to their corresponding elements in the alternative representation.
You may assume that the size of the alternative representation is matching
the size of the "regular" matrix.

Implement the function

```cpp
bool is_equivalent(int** matrix, int* alt_matrix,
                   std::size_t rows, std::size_t cols);
```

Store your code in `matrix.cpp` and the declarations in `matrix.hpp`
(you need to create both files yourself).


# Task 3 - Sort an Array
Implement a function

```cpp
void sort(int* data, std::size_t count);
```

that sorts the given integer array in-place. Do not use any library functions.
You must not create a copy of the array either.
You may implement any sorting algorithm (including your own idea for sorting
an array), however [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort)
is recommended
in this case as it is among the easiest to understand and implement.

Name the source file `sort.cpp` and the header file `sort.hpp`.
