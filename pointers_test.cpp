#include "pointers.hpp"

#include <vector>

#include <catch2/catch_test_macros.hpp>
// #include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using Catch::Matchers::Equals;


TEST_CASE("swap to integers", "[swap]") {
  int a = 0;
  int b = 234;
  int c = 392;
  int d = -392;

  SECTION("single swap") {
    swap(&a, &b);
    swap(&c, &d);

    CHECK(a == 234);
    CHECK(b == 0);
    CHECK(c == -392);
    CHECK(d == 392);
  }


  SECTION("double swap") {
    swap(&a, &b);
    swap(&c, &d);
    swap(&a, &b);
    swap(&c, &d);

    CHECK(a == 0);
    CHECK(b == 234);
    CHECK(c == 392);
    CHECK(d == -392);
  }

  SECTION("mixed swap") {
    swap(&a, &b);
    swap(&c, &d);
    swap(&a, &c);
    swap(&b, &d);

    CHECK(a == -392);
    CHECK(b == 392);
    CHECK(c == 234);
    CHECK(d == 0);
  }
}


TEST_CASE("reverse an array in place", "[reverse]") {
  int a[] = {3};
  int b[] = {0, 1, 2, 3, 7, 8, 9, 10};
  int c[] = {-3, -1, 5, 7};

  SECTION("regular") {
    const int a_val = *a;
    reverse(a, 1);
    CHECK(*a == a_val);

    reverse(b, sizeof(b) / sizeof(int));
    // std::vector<int> b_actual{b, b + sizeof(b) / sizeof(int)};
    std::vector<int> b_actual{b, b + sizeof(b) / sizeof(int)};
    std::vector<int> b_expected{10, 9, 8, 7, 3, 2, 1, 0};
    CHECK_THAT(b_actual, Equals(b_expected));

    reverse(c, sizeof(c) / sizeof(int));
    std::vector<int> c_actual(c, c + sizeof(c) / sizeof(int));
    std::vector<int> c_expected{7, 5, -1, -3};
    CHECK_THAT(c_actual, Equals(c_expected));
  }


  SECTION("double reverse") {
    const int a_val = *a;
    reverse(a, 0);
    reverse(a, 0);
    CHECK(*a == a_val);

    std::vector<int> b_expected(b, b + sizeof(b) / sizeof(int));
    reverse(b, sizeof(b) / sizeof(int));
    reverse(b, sizeof(b) / sizeof(int));
    std::vector<int> b_actual{b, b + sizeof(b) / sizeof(int)};
    CHECK_THAT(b_actual, Equals(b_expected));


    std::vector<int> c_expected(c, c + sizeof(c) / sizeof(int));
    reverse(c, sizeof(c) / sizeof(int));
    reverse(c, sizeof(c) / sizeof(int));
    std::vector<int> c_actual(c, c + sizeof(c) / sizeof(int));
    CHECK_THAT(c_actual, Equals(c_expected));
  }
}


TEST_CASE("find pointer to element in array", "[find]") {
  int a[] = {3};
  int b[] = {0, 1, 2, 3, 7, 8, 9, 10};
  int c[] = {-3, -1, 5, 7};

  SECTION("success") {
    CHECK(find(3, a, 1) == a);
    CHECK(find(3, b, sizeof(b) / sizeof(int)) == b + 3);
    CHECK(find(10, b, sizeof(b) / sizeof(int)) == b + 7);
    CHECK(find(-1, c, sizeof(c) / sizeof(int)) == c + 1);
  }

  SECTION("failure") {
    CHECK(find(4, a, 1) == nullptr);
    CHECK(find(4, b, sizeof(b) / sizeof(int)) == nullptr);
    CHECK(find(-5, c, sizeof(c) / sizeof(int)) == nullptr);
  }
}


TEST_CASE("find pointer to row in matrix containing element", "[find_row]") {
  int** a = new int*[1];
  a[0] = new int[1];
  a[0][0] = 3;

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

  SECTION("success") {
    CHECK(find_containing_row(3, a, 1, 1) == *a);
    CHECK(find_containing_row(3, b, 3, 3) == *(b + 1));
    CHECK(find_containing_row(10, b, 3, 3) == *(b + 2));
  }

  SECTION("failure") {
    CHECK(find_containing_row(4, a, 1, 1) == nullptr);
    CHECK(find_containing_row(4, b, 3, 3) == nullptr);
  }

  delete[] a[0];
  delete[] a;
  delete[] b[0];
  delete[] b[1];
  delete[] b[2];
  delete[] b;
}
