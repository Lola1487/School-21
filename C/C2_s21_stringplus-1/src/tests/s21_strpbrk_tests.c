#include "s21_test_runner.h"

START_TEST(test_strpbrk_found_start) {
  // ARRANGE: Set up test data
  const char *str = "Hello";
  const char *pattern = "He";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: Character found in the middle of the string
 * Checks if the function correctly finds a character from the pattern
 * in the middle of the source string
 */
START_TEST(test_strpbrk_found_middle) {
  // ARRANGE: Set up test data
  const char *str = "School21";
  const char *pattern = "o";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: Character found at the end of the string
 * Checks if the function correctly finds a character from the pattern
 * at the end of the source string
 */
START_TEST(test_strpbrk_found_end) {
  // ARRANGE: Set up test data
  const char *str = "Programming";
  const char *pattern = "g";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: Character not found in the string
 * Checks if the function correctly returns NULL when no characters
 * from the pattern are found in the source string
 */
START_TEST(test_strpbrk_not_found) {
  // ARRANGE: Set up test data
  const char *str = "Testing";
  const char *pattern = "xyz";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: Empty pattern
 * Checks if the function correctly handles an empty pattern string
 */
START_TEST(test_strpbrk_empty_pattern) {
  // ARRANGE: Set up test data
  const char *str = "Function";
  const char *pattern = "";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: Empty source string
 * Checks if the function correctly handles an empty source string
 */
START_TEST(test_strpbrk_empty_string) {
  // ARRANGE: Set up test data
  const char *str = "";
  const char *pattern = "test";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: Full match between string and pattern
 * Checks if the function correctly handles when the source string
 * and pattern contain the same characters
 */
START_TEST(test_strpbrk_full_match) {
  // ARRANGE: Set up test data
  const char *str = "code";
  const char *pattern = "code";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: Multiple potential matches
 * Checks if the function correctly finds the first matching character
 * when multiple characters from the pattern exist in the source string
 */
START_TEST(test_strpbrk_multiple_matches) {
  // ARRANGE: Set up test data
  const char *str = "developer";
  const char *pattern = "er";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: String with only spaces that match
 * Checks if the function correctly handles a string with only whitespace
 * characters when the pattern contains a space
 */
START_TEST(test_strpbrk_only_spaces_match) {
  // ARRANGE: Set up test data
  const char *str = "     ";
  const char *pattern = " ";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: String with only spaces that don't match
 * Checks if the function correctly returns NULL for a string with only
 * whitespace characters when the pattern doesn't contain a space
 */
START_TEST(test_strpbrk_only_spaces_no_match) {
  // ARRANGE: Set up test data
  const char *str = "     ";
  const char *pattern = "c";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: String with escape sequences
 * Checks if the function correctly handles escape sequences in both
 * the source string and pattern
 */
START_TEST(test_strpbrk_escape_sequences) {
  // ARRANGE: Set up test data
  const char *str = "String\nWith\tEscapes";
  const char *pattern = "\n\t";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: String with high ASCII characters
 * Checks if the function correctly handles characters outside the
 * standard ASCII range
 */
START_TEST(test_strpbrk_high_ascii) {
  // ARRANGE: Set up test data
  const char *str = "\xC3\xB1";
  const char *pattern = "\xB1";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Test: Both string and pattern are empty
 * Checks if the function correctly handles when both input strings are empty
 */
START_TEST(test_strpbrk_both_empty) {
  // ARRANGE: Set up test data
  const char *str = "";
  const char *pattern = "";

  // ACT: Execute the function under test
  char *result = s21_strpbrk(str, pattern);
  char *expected = strpbrk(str, pattern);

  // ASSERT: Verify the result
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * Creates and returns a test suite for the s21_strpbrk function
 */
Suite *tests_for_strpbrk(void) {
  Suite *s;
  TCase *tc_strpbrk;

  // Create suite and test case
  s = suite_create("strpbrk_tests");
  tc_strpbrk = tcase_create("tc_strpbrk");

  // Add test cases to the test suite
  tcase_add_test(tc_strpbrk, test_strpbrk_found_start);
  tcase_add_test(tc_strpbrk, test_strpbrk_found_middle);
  tcase_add_test(tc_strpbrk, test_strpbrk_found_end);
  tcase_add_test(tc_strpbrk, test_strpbrk_not_found);
  tcase_add_test(tc_strpbrk, test_strpbrk_empty_pattern);
  tcase_add_test(tc_strpbrk, test_strpbrk_empty_string);
  tcase_add_test(tc_strpbrk, test_strpbrk_full_match);
  tcase_add_test(tc_strpbrk, test_strpbrk_multiple_matches);
  tcase_add_test(tc_strpbrk, test_strpbrk_only_spaces_match);
  tcase_add_test(tc_strpbrk, test_strpbrk_only_spaces_no_match);
  tcase_add_test(tc_strpbrk, test_strpbrk_escape_sequences);
  tcase_add_test(tc_strpbrk, test_strpbrk_high_ascii);
  tcase_add_test(tc_strpbrk, test_strpbrk_both_empty);

  suite_add_tcase(s, tc_strpbrk);

  return s;
}
