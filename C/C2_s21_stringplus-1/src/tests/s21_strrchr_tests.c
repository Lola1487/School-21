#include "s21_test_runner.h"

START_TEST(test_strrchr_found_end) {
  // ARRANGE
  const char *str = "Hello, World!";
  int c = '!';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: Character found in the middle of the string.
 *
 * This test checks if the function correctly finds a character located
 * in the middle of the string.
 */
START_TEST(test_strrchr_found_middle) {
  // ARRANGE
  const char *str = "Programming";
  int c = 'g';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: Character found at the start of the string.
 *
 * This test checks if the function correctly finds a character located
 * at the start of the string.
 */
START_TEST(test_strrchr_found_start) {
  // ARRANGE
  const char *str = "Algorithm";
  int c = 'A';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: Character not found in the string.
 *
 * This test checks if the function correctly handles the case when the
 * specified character is not present in the string.
 */
START_TEST(test_strrchr_not_found) {
  // ARRANGE
  const char *str = "OpenAI";
  int c = 'z';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: Searching for the null terminator character.
 *
 * This test checks if the function correctly finds the null terminator
 * character (`\0`) in the string.
 */
START_TEST(test_strrchr_null_char) {
  // ARRANGE
  const char *str = "Data Science";
  int c = '\0';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: String with multiple occurrences of the character.
 *
 * This test checks if the function correctly finds the last occurrence
 * of a character when there are multiple instances in the string.
 */
START_TEST(test_strrchr_multiple_occurrences) {
  // ARRANGE
  const char *str = "banana";
  int c = 'a';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: String consisting of a single character.
 *
 * This test checks if the function correctly handles a string that
 * contains only one character.
 */
START_TEST(test_strrchr_single_char) {
  // ARRANGE
  const char *str = "X";
  int c = 'X';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: Empty string.
 *
 * This test checks if the function correctly handles an empty string.
 */
START_TEST(test_strrchr_empty_string) {
  // ARRANGE
  const char *str = "";
  int c = 'a';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: String containing spaces.
 *
 * This test checks if the function correctly finds a space character
 * in a string that contains spaces.
 */
START_TEST(test_strrchr_with_spaces) {
  // ARRANGE
  const char *str = "Coding is fun";
  int c = ' ';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: String with non-printable ASCII characters.
 *
 * This test checks if the function correctly handles non-printable
 * ASCII characters in the string.
 */
START_TEST(test_strrchr_ascii) {
  // ARRANGE
  const char str[] = {'a', 'b', 'c', '\x7F', 'd', 'e', 'f', '\0'};
  int c = '\x7F';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: String with repeated characters, last character matches.
 *
 * This test checks if the function correctly finds the last occurrence
 * of a character when the string consists of repeated characters.
 */
START_TEST(test_strrchr_repeated_last_char) {
  // ARRANGE
  const char *str = "zzzzzz";
  int c = 'z';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test: String with mixed characters (letters, numbers, symbols).
 *
 * This test checks if the function correctly finds a character in a string
 * that contains a mix of letters, numbers, and symbols.
 */
START_TEST(test_strrchr_mixed_chars) {
  // ARRANGE
  const char *str = "abc123!@#";
  int c = '2';

  // ACT
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);

  // ASSERT
  ck_assert_ptr_eq(result, expected);
}
END_TEST

/**
 * @brief Test suite for the s21_strrchr function.
 *
 * This function creates and returns a test suite containing all the test cases
 * for the `s21_strrchr` function.
 *
 * @return A pointer to the test suite.
 */
Suite *tests_for_strrchr(void) {
  Suite *s;
  TCase *tc_strrchr;

  s = suite_create("strrchr_tests");
  tc_strrchr = tcase_create("strrchr_tc");

  tcase_add_test(tc_strrchr, test_strrchr_found_end);
  tcase_add_test(tc_strrchr, test_strrchr_found_middle);
  tcase_add_test(tc_strrchr, test_strrchr_found_start);
  tcase_add_test(tc_strrchr, test_strrchr_not_found);
  tcase_add_test(tc_strrchr, test_strrchr_null_char);
  tcase_add_test(tc_strrchr, test_strrchr_multiple_occurrences);
  tcase_add_test(tc_strrchr, test_strrchr_single_char);
  tcase_add_test(tc_strrchr, test_strrchr_empty_string);
  tcase_add_test(tc_strrchr, test_strrchr_with_spaces);
  tcase_add_test(tc_strrchr, test_strrchr_ascii);
  tcase_add_test(tc_strrchr, test_strrchr_repeated_last_char);
  tcase_add_test(tc_strrchr, test_strrchr_mixed_chars);

  suite_add_tcase(s, tc_strrchr);

  return s;
}
