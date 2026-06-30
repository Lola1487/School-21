#include "s21_test_runner.h"

START_TEST(s21_strncat_basic_functionality) {
  /* ARRANGE */
  char expected_result[32] = "string";
  char actual_result[32] = "string";
  const char *src = "additional_text";

  /* ACT */
  strncat(expected_result, src, 13);  // Appending first 13 characters from src
  s21_strncat(actual_result, src, 13);  // Same action using our function

  /* ASSERT */
  ck_assert_str_eq(expected_result, actual_result);
}
END_TEST

/**
 * @test Checks behavior of s21_strncat when concatenating empty strings.
 * This test verifies that the function handles cases where the source string is
 * empty.
 */
START_TEST(s21_strncat_empty_strings) {
  /* ARRANGE */
  char expected_result[32] = "initial_value";
  char actual_result[32] = "initial_value";
  const char *empty_src = "";  // Empty string

  /* ACT */
  strncat(expected_result, empty_src,
          10);  // Attempt to concatenate an empty string
  s21_strncat(actual_result, empty_src, 10);  // Same action using our function

  /* ASSERT */
  ck_assert_str_eq(expected_result, actual_result);
}
END_TEST

/**
 * @test Verifies the behavior of s21_strncat when passing zero as parameter n.
 * This test ensures that no characters are appended if n equals zero.
 */
START_TEST(s21_strncat_zero_n_parameter) {
  /* ARRANGE */
  char expected_result[32] = "base_string";
  char actual_result[32] = "base_string";
  const char *src = "some_data";

  /* ACT */
  strncat(expected_result, src, 0);  // Standard function should ignore copying
  s21_strncat(actual_result, src,
              0);  // Our function should also ignore copying

  /* ASSERT */
  ck_assert_str_eq(expected_result, actual_result);
}
END_TEST

/**
 * @test Ensures proper handling when the length of the appended string exceeds
 * the source's length. This test checks that the function works correctly even
 * when the number of characters to copy exceeds the length of the source
 * string.
 */
START_TEST(s21_strncat_longer_than_source_length) {
  /* ARRANGE */
  char expected_result[32] = "short_string";
  char actual_result[32] = "short_string";
  const char *src = "long";  // The length of this string is less than the
                             // specified number of characters

  /* ACT */
  strncat(expected_result, src, 20);    // Should copy the entire 'long' string
  s21_strncat(actual_result, src, 20);  // Same action using our function

  /* ASSERT */
  ck_assert_str_eq(expected_result, actual_result);
}
END_TEST

/**
 * @test Checks whether s21_strncat returns the correct pointer.
 * This test verifies that the function returns a valid pointer to the resulting
 * string.
 */
START_TEST(s21_strncat_return_pointer_check) {
  /* ARRANGE */
  char expected_result[32] = "prefix";
  char actual_result[32] = "prefix";
  const char *src = "_suffix";

  /* ACT */
  strncat(expected_result, src,
          7);  // Standard function returns a pointer to the result
  char *result = s21_strncat(actual_result, src,
                             7);  // Our function should also return a pointer

  /* ASSERT */
  ck_assert_str_eq(expected_result, actual_result);
  ck_assert_ptr_eq(result, actual_result);
}
END_TEST

Suite *tests_for_strncat(void) {
  /**
   * @brief Creates a suite of tests for the s21_strncat function.
   * This function creates and returns a suite of tests for testing various
   * aspects of the s21_strncat function.
   * @return A pointer to the created test suite.
   */
  Suite *s;
  TCase *tc_strncat;

  s = suite_create("strncat_tests");  // Create a new test suite
  tc_strncat =
      tcase_create("strncat_test_cases");  // Create a new test case group

  tcase_add_test(
      tc_strncat,
      s21_strncat_basic_functionality);  // Add basic functionality tests
  tcase_add_test(
      tc_strncat,
      s21_strncat_empty_strings);  // Tests for handling empty strings
  tcase_add_test(
      tc_strncat,
      s21_strncat_zero_n_parameter);  // Tests for zero value of parameter n
  tcase_add_test(
      tc_strncat,
      s21_strncat_longer_than_source_length);  // Tests for longer-than-source
                                               // lengths
  tcase_add_test(tc_strncat,
                 s21_strncat_return_pointer_check);  // Tests for returned
                                                     // pointer correctness

  suite_add_tcase(s, tc_strncat);  // Add the test case group to the suite

  return s;  // Return the completed test suite
}
