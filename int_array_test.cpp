#include "int_array.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stddef.h>


IntArray* ia_empty = NULL;
IntArray* ia_12345 = NULL;
IntArray* ia_567 = NULL;

void setup(void) {
  ia_empty = (IntArray*) malloc(sizeof(IntArray));
  ia_empty->reserved = 10;
  ia_empty->elements = 0;
  ia_empty->array = (int*) malloc(ia_empty->reserved * sizeof(int));

  ia_12345 = (IntArray*) malloc(sizeof(IntArray));
  ia_12345->reserved = 10;
  ia_12345->elements = 5;
  ia_12345->array = (int*) malloc(ia_12345->reserved * sizeof(int));
  ia_12345->array[0] = 1;
  ia_12345->array[1] = 2;
  ia_12345->array[2] = 3;
  ia_12345->array[3] = 4;
  ia_12345->array[4] = 5;

  ia_567 = (IntArray*) malloc(sizeof(IntArray));
  ia_567->reserved = 10;
  ia_567->elements = 3;
  ia_567->array = (int*) malloc(ia_567->reserved * sizeof(int));
  ia_567->array[0] = 5;
  ia_567->array[1] = 6;
  ia_567->array[2] = 7;
}

void teardown(void) {
  free(ia_empty->array);
  free(ia_empty);
  free(ia_12345->array);
  free(ia_12345);
  free(ia_567->array);
  free(ia_567);
}

Test(int_array, ia_create) {
  IntArray* ia = ia_create();

  cr_assert(eq(int, ia->elements, 0), "New IntArray must be empty.");

  free(ia->array);
  free(ia);
}

Test(int_array, ia_zeros) {
  IntArray* ia1 = ia_zeros(0);
  IntArray* ia2 = ia_zeros(20);
  IntArray* ia3 = ia_zeros(2000);

  cr_assert(eq(int, ia1->elements, 0), "No zeros expected.");
  cr_assert(eq(int, ia2->elements, 20), "20 zeros expected.");
  cr_assert(ge(int, ia2->reserved, 20), "Array size >= 20 expected.");
  int expected_20[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  cr_assert(eq(int[20], ia2->array, expected_20), "correct array expected.");
  cr_assert(eq(int, ia3->elements, 2000), "2000 zeros expected.");
  cr_assert(ge(int, ia3->reserved, 2000), "Array size >= 2000 expected.");

  free(ia1->array);
  free(ia1);
  free(ia2->array);
  free(ia2);
  free(ia3->array);
  free(ia3);
}

Test(int_array, ia_ones) {
  IntArray* ia1 = ia_ones(0);
  IntArray* ia2 = ia_ones(20);
  IntArray* ia3 = ia_ones(2000);

  cr_assert(eq(int, ia1->elements, 0), "No elements expected.");
  cr_assert(eq(int, ia2->elements, 20), "20 elements expected.");
  cr_assert(ge(int, ia2->reserved, 20), "Array size >= 20 expected.");
  int expected_20[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
  cr_assert(eq(int[20], ia2->array, expected_20), "correct array expected.");
  cr_assert(eq(int, ia3->elements, 2000), "2000 elements expected.");
  cr_assert(ge(int, ia3->reserved, 2000), "Array size >= 2000 expected.");

  free(ia1->array);
  free(ia1);
  free(ia2->array);
  free(ia2);
  free(ia3->array);
  free(ia3);
}

Test(int_array, ia_range) {
  IntArray* ia1 = ia_range(0, 0);
  IntArray* ia2 = ia_range(0, 20);
  IntArray* ia3 = ia_range(0, 2000);
  IntArray* ia4 = ia_range(15, 30);

  cr_assert(eq(int, ia1->elements, 0), "No elements expected.");
  cr_assert(eq(int, ia2->elements, 20), "20 elements expected.");
  cr_assert(ge(int, ia2->reserved, 20), "Array size >= 20 expected.");
  int expected_20[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
  cr_assert(eq(int[20], ia2->array, expected_20), "correct array expected.");
  cr_assert(eq(int, ia3->elements, 2000), "2000 elements expected.");
  cr_assert(ge(int, ia3->reserved, 2000), "Array size >= 2000 expected.");
  cr_assert(eq(int, ia4->elements, 15), "15 elements expected.");
  cr_assert(ge(int, ia4->reserved, 15), "Array size >= 15 expected.");
  int expected_ia4[] = {15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};
  cr_assert(eq(int[15], ia4->array, expected_ia4), "correct array expected.");

  free(ia1->array);
  free(ia1);
  free(ia2->array);
  free(ia2);
  free(ia3->array);
  free(ia3);
  free(ia4->array);
  free(ia4);
}

/*
 * There is no real way to check if free was called, so the only check made
 * is whether the pointers have been set to NULL.
 */
Test(int_array, ia_free) {
  IntArray* ia = (IntArray*) malloc(sizeof(IntArray));
  ia->reserved = 10;
  ia->elements = 0;
  ia->array = (int*) malloc(ia->reserved * sizeof(int));
  IntArray* ia_ptr = ia;  // allow to reference member of destroyed object
  ia = ia_free(ia);
  cr_assert(eq(ptr, ia_ptr->array, NULL), "Array must be freed.");
  cr_assert(eq(ptr, ia, NULL), "IntArray must be freed.");
}


Test(int_array, ia_push_back) {
  IntArray* ia = (IntArray*) malloc(sizeof(IntArray));
  ia->reserved = 2;
  ia->elements = 1;
  ia->array = (int*) malloc(ia->reserved * sizeof(int));
  ia->array[0] = 10;
  ia_push_back(ia, 15);
  cr_assert(eq(sz, ia->elements, 2), "Element must be added.");
  cr_assert(eq(sz, ia->reserved, 2), "No additional memory must be required.");
  cr_assert(eq(int, ia->array[0], 10), "Initial element must not be changed.");
  cr_assert(eq(int, ia->array[1], 15), "New element must be added.");

  ia_push_back(ia, 17);
  cr_assert(eq(sz, ia->elements, 3), "Element must be added.");
  cr_assert(ge(sz, ia->reserved, 3), "Additional memory must be allocated.");
  cr_assert(eq(int, ia->array[0], 10), "Initial element must not be changed.");
  cr_assert(eq(int, ia->array[1], 15), "Second element must not be changed.");
  cr_assert(eq(int, ia->array[2], 17), "New element must be added.");
  free(ia->array);
  free(ia);
}

Test(int_array, ia_pop_back) {
  IntArray* ia = (IntArray*) malloc(sizeof(IntArray));
  ia->reserved = 2;
  ia->elements = 2;
  ia->array = (int*) malloc(ia->reserved * sizeof(int));
  ia->array[0] = 10;
  ia->array[1] = 15;

  int val = ia_pop_back(ia);
  cr_assert(eq(sz, ia->elements, 1), "Element must be removed.");
  cr_assert(eq(int, ia->array[0], 10), "First element must not be changed.");
  cr_assert(eq(int, val, 15), "Last element must be returned.");

  val = ia_pop_back(ia);
  cr_assert(eq(sz, ia->elements, 0), "Element must be removed.");
  cr_assert(eq(int, val, 10), "Last element must be returned.");

  free(ia->array);
  free(ia);
}

Test(int_array, ia_size, .init = setup, .fini = teardown) {
  cr_assert(eq(sz, ia_size(ia_empty), 0), "Show correct size of empty array.");
  cr_assert(eq(sz, ia_size(ia_567), 3), "Show correct size of array.");
}

Test(int_array, ia_count, .init = setup, .fini = teardown) {
  IntArray* ia3 = (IntArray*) malloc(sizeof(IntArray));
  ia3->reserved = 9;
  ia3->elements = 3;
  ia3->array = (int*) malloc(ia3->reserved * sizeof(int));
  ia3->array[0] = 10;
  ia3->array[1] = 15;
  ia3->array[2] = 10;

  cr_assert(eq(sz, ia_count(ia_empty, 10), 0), "10 is not in the array.");
  cr_assert(eq(sz, ia_count(ia3, 10), 2), "10 is twice in the array.");

  free(ia3->array);
  free(ia3);
}

Test(int_array, ia_index, .init = setup, .fini = teardown) {
  cr_assert(eq(sz, ia_index(ia_567, 0), 5), "The first element is 5.");
  cr_assert(eq(sz, ia_index(ia_567, 1), 6), "The second element is 6.");
  cr_assert(eq(sz, ia_index(ia_567, 2), 7), "The third element is 7.");
}

Test(int_array, ia_sum, .init = setup, .fini = teardown) {
  cr_assert(eq(long, ia_sum(ia_empty), 0), "The sum of the empty array is 0.");
  cr_assert(eq(long, ia_sum(ia_12345), 15), "The sum should be 15.");
  cr_assert(eq(long, ia_sum(ia_567), 18), "The sum should be 18.");
}

Test(int_array, ia_add, .init = setup, .fini = teardown) {
  IntArray* first = ia_add(ia_567, ia_12345);
  IntArray* second = ia_add(ia_12345, ia_567);
  int expected[] = {6, 8, 10, 4, 5};

  cr_assert(eq(int[5], first->array, expected), "Add longer to shorter.");
  cr_assert(eq(int[5], second->array, expected), "Add shorter to longer.");

  free(first->array);
  free(first);
  free(second->array);
  free(second);
}

Test(int_array, ia_add_same_size, .init = setup, .fini = teardown) {
  IntArray* ia = ia_add(ia_567, ia_567);
  int expected[] = {10, 12, 14};

  cr_assert(eq(int[3], ia->array, expected), "Add same size.");

  free(ia->array);
  free(ia);
}

Test(int_array, ia_add_empty, .init = setup, .fini = teardown) {
  IntArray* first = ia_add(ia_empty, ia_567);
  IntArray* second = ia_add(ia_567, ia_empty);

  cr_assert(eq(int[3], first->array, ia_567->array), "Added to empty.");
  cr_assert(eq(int[3], second->array, ia_567->array), "Empty added.");

  free(first->array);
  free(first);
  free(second->array);
  free(second);
}

Test(int_array, ia_mul, .init = setup, .fini = teardown) {
  IntArray* first = ia_mul(ia_567, ia_12345);
  IntArray* second = ia_mul(ia_12345, ia_567);
  int expected[] = {5, 12, 21, 4, 5};

  cr_assert(eq(int[5], first->array, expected), "Multiply with longer.");
  cr_assert(eq(int[5], second->array, expected), "Multiply with shorter.");

  free(first->array);
  free(first);
  free(second->array);
  free(second);
}

Test(int_array, ia_mul_same_size, .init = setup, .fini = teardown) {
  IntArray* ia = ia_mul(ia_567, ia_567);
  int expected[] = {25, 36, 49};

  cr_assert(eq(int[3], ia->array, expected), "Multiply same size.");

  free(ia->array);
  free(ia);
}

Test(int_array, ia_mul_empty, .init = setup, .fini = teardown) {
  IntArray* first = ia_mul(ia_empty, ia_567);
  IntArray* second = ia_mul(ia_567, ia_empty);

  cr_assert(eq(int[3], first->array, ia_567->array), "Empty multiplied.");
  cr_assert(eq(int[3], second->array, ia_567->array), "Multiply with empty.");

  free(first->array);
  free(first);
  free(second->array);
  free(second);
}
