#include "matrix.hpp"

#include <cstdint>

#include <catch2/catch_test_macros.hpp>


TEST_CASE("test if matrices are equivalent", "[equivalent]") {
  int** a = new int*[1];
  a[0] = new int[1];
  a[0][0] = 3;
  int a_alt[] = {3};
  int a_alt_different[] = {5};

  CHECK(is_equivalent(a, a_alt, 1, 1));
  CHECK(not is_equivalent(a, a_alt_different, 1, 1));

  int** b = new int*[3];
  b[0] = new int[3];
  b[1] = new int[3];
  b[2] = new int[3];
  b[0][0] = 0;
  b[0][1] = 1;
  b[0][2] = 2;
  b[1][0] = 3;
  b[1][1] = 7;
  b[1][2] = 8;
  b[2][0] = 9;
  b[2][1] = 10;
  b[2][2] = 11;
  int b_alt[] = { 0, 1, 2, 3, 7, 8, 9, 10, 11 };
  int b_alt_different[] = { 0, 1, 2, 3, 7, 8, 9, 10, 10 };
  int b_alt_different_minus[] = { 0, 1, 2, 3, -7, 8, 9, 10, 11 };

  CHECK(is_equivalent(b, b_alt, 3, 3));
  CHECK(not is_equivalent(b, b_alt_different, 3, 3));
  CHECK(not is_equivalent(b, b_alt_different_minus, 3, 3));
}

