#include "../s21_string.h"
#include "s21_test_runner.h"

// Test: character found in the middle of the string
START_TEST(test_strcspn_found_middle) {
  // ARRANGE
  const char* STR_1 = "Test string";
  const char* STR_2 = "i";

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: character found at the start of the string
START_TEST(test_strcspn_found_start) {
  // ARRANGE
  const char* STR_1 = "Test string";
  const char* STR_2 = "T";

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: character found at the end of the string
START_TEST(test_strcspn_found_end) {
  // ARRANGE
  const char* STR_1 = "Test string";
  const char* STR_2 = "g";

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: character not found
START_TEST(test_strcspn_not_found) {
  // ARRANGE
  const char* STR_1 = "Test string";
  const char* STR_2 = "Z";

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: empty search string
START_TEST(test_strcspn_empty_search) {
  // ARRANGE
  const char* STR_1 = "Test string";
  const char* STR_2 = "";

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: search string contains all characters from the source string
START_TEST(test_strcspn_full_match) {
  // ARRANGE
  const char* STR_1 = "Teststring";
  const char* STR_2 = "Teststring";

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: search string contains characters not present in the source string
START_TEST(test_strcspn_no_overlap) {
  // ARRANGE
  const char* STR_1 = "Teststring";
  const char* STR_2 = "XYZ";

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: source string consists only of spaces
START_TEST(test_strcspn_only_spaces) {
  // ARRANGE
  const char* STR_1 = "          ";  // Source string consisting only of spaces
  const char* STR_2 = " ";           // Search string with a single space

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: high ASCII characters are used in the search
START_TEST(test_strcspn_high_ascii) {
  // ARRANGE
  const char* STR_1 =
      "Test\xF1 string";       // Source string with high ASCII character
  const char* STR_2 = "\xF1";  // High ASCII character for search

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

// Test: character found in a long string
START_TEST(test_strcspn_first_char_in_long_string) {
  // ARRANGE
  char STR_1[1000];         // Long character array
  memset(STR_1, 'A', 999);  // Fill the array with 'A'
  STR_1[0] = 'B';           // Change the first character to 'B'
  STR_1[999] = '\0';        // Ensure the string is null-terminated

  const char* STR_2 = "B";  // Character to find

  // ACT
  s21_size_t result = s21_strcspn(STR_1, STR_2);

  // ASSERT
  ck_assert_int_eq(result, strcspn(STR_1, STR_2));
}
END_TEST

/**
 * @brief Creates a test suite for `s21_strcspn`.
 *
 * @return The created test suite.
 */
Suite* tests_for_strcspn() {
  Suite* s = suite_create("strcspn_tests");        // Create the test suite
  TCase* tc_strcspn = tcase_create("tc_strcspn");  // Create a test case

  // Add individual tests to the test case
  tcase_add_test(tc_strcspn, test_strcspn_found_middle);
  tcase_add_test(tc_strcspn, test_strcspn_found_start);
  tcase_add_test(tc_strcspn, test_strcspn_found_end);
  tcase_add_test(tc_strcspn, test_strcspn_not_found);
  tcase_add_test(tc_strcspn, test_strcspn_empty_search);
  tcase_add_test(tc_strcspn, test_strcspn_full_match);
  tcase_add_test(tc_strcspn, test_strcspn_no_overlap);
  tcase_add_test(tc_strcspn, test_strcspn_only_spaces);
  tcase_add_test(tc_strcspn, test_strcspn_high_ascii);
  tcase_add_test(tc_strcspn, test_strcspn_first_char_in_long_string);

  // Add the test case to the suite
  suite_add_tcase(s, tc_strcspn);

  return s;  // Return the completed test suite
}
