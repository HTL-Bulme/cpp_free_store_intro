#include "sort.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using std::vector;
using Catch::Matchers::Equals;

TEST_CASE("sorting an array in-place", "[sort]") {
  int a[] = {3};
  int b[] = {0, 1, 2, 3, 8, 7, 9, 10};
  int c[] = {10, 9, 8, -3, 2, -1, 0};

  sort(a, sizeof(a) / sizeof(int));
  sort(b, sizeof(b) / sizeof(int));
  sort(c, sizeof(c) / sizeof(int));

  vector<int> a_sorted = {3};
  vector<int> b_sorted = {0, 1, 2, 3, 7, 8, 9, 10};
  vector<int> c_sorted = {-3, -1, 0, 2, 8, 9, 10};

  std::vector<int> a_actual{a, a + sizeof(a) / sizeof(int)};
  std::vector<int> b_actual{b, b + sizeof(b) / sizeof(int)};
  std::vector<int> c_actual{c, c + sizeof(c) / sizeof(int)};

  CHECK_THAT(a_actual, Equals(a_sorted));
  CHECK_THAT(b_actual, Equals(b_sorted));
  CHECK_THAT(c_actual, Equals(c_sorted));
}



