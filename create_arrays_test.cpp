#include "create_arrays.h"

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stddef.h>

Test(create_arrays, zeros) {
  int* a0 = zeros(1);
  int* a1 = zeros(5);
  int* a2 = zeros(50000);
  int expected[] = {0, 0, 0, 0, 0};

  cr_expect(eq(int, a0[0], 0), "Element is 0.");
  cr_expect(eq(int[5], a1, expected), "Elements are 00000.");
  cr_expect(eq(int, a2[0], 0), "First element is 0.");
  cr_expect(eq(int, a2[49999], 0), "Last element is 0.");

  free(a0);
  free(a1);
  free(a2);
}

Test(create_arrays, ones) {
  int* a0 = ones(1);
  int* a1 = ones(5);
  int* a2 = ones(50000);
  int expected[] = {1, 1, 1, 1, 1};

  cr_expect(eq(int, a0[0], 1), "Element is 1.");
  cr_expect(eq(int[5], a1, expected), "Elements are 11111.");
  cr_expect(eq(int, a2[0], 1), "First element is 1.");
  cr_expect(eq(int, a2[49999], 1), "Last element is 1.");

  free(a0);
  free(a1);
  free(a2);
}

Test(create_arrays, range) {
  int* a0 = range(1);
  int* a1 = range(5);
  int* a2 = range(50000);
  int expected[] = {0, 1, 2, 3, 4};

  cr_expect(eq(int, a0[0], 0), "Element is 0.");
  cr_expect(eq(int[5], a1, expected), "Elements are 01234.");
  cr_expect(eq(int, a2[0], 0), "First element is 0.");
  cr_expect(eq(int, a2[49999], 49999), "Last element is 49999.");

  free(a0);
  free(a1);
  free(a2);
}
