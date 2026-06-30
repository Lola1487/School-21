#include "s21_test_runner.h"

START_TEST(s21_strncpy_full_copy) {
  // ARRANGE
  const char* src = "hello_world";
  char* dest_std;
  char* dest_custom;
  dest_std = malloc(32);
  dest_custom = malloc(32);
  memset(dest_std, 42, 32);  // Fill with a non-zero value
  memset(dest_custom, 42, 32);

  // ACT
  strncpy(dest_std, src, 32);         // Standard library function
  s21_strncpy(dest_custom, src, 32);  // Custom implementation

  // ASSERT
  ck_assert_mem_eq(dest_std, dest_custom, 32);  // Compare results

  // Clean up
  free(dest_std);
  free(dest_custom);
}
END_TEST

/**
 * @brief Test case for copying a partial string with s21_strncpy.
 *
 * This test checks if s21_strncpy correctly copies a partial string
 * into a destination buffer, ensuring that only the specified number
 * of characters are copied.
 */
START_TEST(s21_strncpy_partial_copy) {
  // ARRANGE
  const char* src = "hello_world";
  char* dest_std;
  char* dest_custom;
  char* ret_custom;
  dest_std = malloc(32);
  dest_custom = malloc(32);
  strncpy(dest_std, "initial_value", 15);  // Pre-fill with some data
  strncpy(dest_custom, "initial_value", 15);

  // ACT
  strncpy(dest_std, src, 10);                      // Standard library function
  ret_custom = s21_strncpy(dest_custom, src, 10);  // Custom implementation

  // ASSERT
  ck_assert_mem_eq(dest_std, dest_custom, 15);  // Compare results
  ck_assert_ptr_eq(dest_custom, ret_custom);    // Check return value

  // Clean up
  free(dest_std);
  free(dest_custom);
}
END_TEST

/**
 * @brief Test case for copying a string with exact length using s21_strncpy.
 *
 * This test checks if s21_strncpy correctly copies a string when the
 * number of characters to copy matches the length of the source string.
 */
START_TEST(s21_strncpy_exact_length) {
  // ARRANGE
  const char* src = "hello_world";
  char* dest_std;
  char* dest_custom;
  char* ret_custom;
  dest_std = malloc(32);
  dest_custom = malloc(32);
  memset(dest_std, 42, 32);  // Fill with a non-zero value
  memset(dest_custom, 42, 32);

  // ACT
  strncpy(dest_std, src, 11);                      // Standard library function
  ret_custom = s21_strncpy(dest_custom, src, 11);  // Custom implementation

  // ASSERT
  ck_assert_mem_eq(dest_std, dest_custom, 32);  // Compare results
  ck_assert_ptr_eq(dest_custom, ret_custom);    // Check return value

  // Clean up
  free(dest_std);
  free(dest_custom);
}
END_TEST

/**
 * @brief Test suite for s21_strncpy.
 *
 * This function creates and returns a test suite containing all the
 * test cases for the s21_strncpy function.
 *
 * @return A pointer to the test suite.
 */
Suite* tests_for_strncpy(void) {
  Suite* s;
  TCase* tc_strncpy;

  s = suite_create("s21_strncpy_tests");
  tc_strncpy = tcase_create("s21_strncpy_tc");

  tcase_add_test(tc_strncpy, s21_strncpy_full_copy);
  tcase_add_test(tc_strncpy, s21_strncpy_partial_copy);
  tcase_add_test(tc_strncpy, s21_strncpy_exact_length);

  suite_add_tcase(s, tc_strncpy);

  return s;
}
