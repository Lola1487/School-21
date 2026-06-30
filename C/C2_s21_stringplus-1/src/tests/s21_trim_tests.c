// #include "../s21_string.h"
#include "s21_test_runner.h"

// Macros for convenience in testing strings
#define STR_EMPTY ""
#define STR_TRIM_CHARS " "

// Delimiters for the first test
#define TRIMMED_STR_1 "***Hello World!***"
#define TRIMS_1 "*"
#define EXPECTED_RESULT_1 "Hello World!"

// Delimiters for the second test
#define TRIMMED_STR_2 "!@!@!#Good Morning Sunshine!#!@!@"
#define TRIMS_2 "!@"
#define EXPECTED_RESULT_2 "#Good Morning Sunshine!#"

// Delimiters for the third test
#define TRIMMED_STR_3 "$$Beautiful Day$$"
#define TRIMS_3 "$"
#define EXPECTED_RESULT_3 "Beautiful Day"

// Test 1: Trimming '*' characters from the beginning and end of the string
START_TEST(test_s21_trim_1) {
  // Arrange
  const char *input_str = TRIMMED_STR_1;
  const char *trims = TRIMS_1;
  const char *expected_output = EXPECTED_RESULT_1;

  // Act
  char *result = s21_trim(input_str, trims);

  // Assert
  ck_assert_str_eq(result, expected_output);
  free(result);
}
END_TEST

// Test 2: Trimming '!@' characters from the beginning and end of the string
START_TEST(test_s21_trim_2) {
  // Arrange
  const char *input_str = TRIMMED_STR_2;
  const char *trims = TRIMS_2;
  const char *expected_output = EXPECTED_RESULT_2;

  // Act
  char *result = s21_trim(input_str, trims);

  // Assert
  ck_assert_str_eq(result, expected_output);
  free(result);
}
END_TEST

// Test 3: Trimming '$' characters from the beginning and end of the string
START_TEST(test_s21_trim_3) {
  // Arrange
  const char *input_str = TRIMMED_STR_3;
  const char *trims = TRIMS_3;
  const char *expected_output = EXPECTED_RESULT_3;

  // Act
  char *result = s21_trim(input_str, trims);

  // Assert
  ck_assert_str_eq(result, expected_output);
  free(result);
}
END_TEST

// Test 4: Empty input string
START_TEST(test_s21_trim_empty_input) {
  // Arrange
  const char *input_str = STR_EMPTY;
  const char *trims = STR_TRIM_CHARS;
  const char *expected_output = STR_EMPTY;

  // Act
  char *result = s21_trim(input_str, trims);

  // Assert
  ck_assert_str_eq(result, expected_output);
  free(result);
}
END_TEST

// Test 5: Input string is NULL
START_TEST(test_s21_trim_null_input) {
  // Arrange
  const char *input_str = s21_NULL;
  const char *trims = STR_TRIM_CHARS;
  const char *expected_output = s21_NULL;

  // Act
  char *result = s21_trim(input_str, trims);

  // Assert
  ck_assert_ptr_eq(result, expected_output);
  free(result);
}
END_TEST

// Building the test suite
Suite *tests_for_trim(void) {
  Suite *s;
  TCase *tc_trim;

  s = suite_create("Trim Tests");
  tc_trim = tcase_create("Core Functionality");

  tcase_add_test(tc_trim, test_s21_trim_1);
  tcase_add_test(tc_trim, test_s21_trim_2);
  tcase_add_test(tc_trim, test_s21_trim_3);
  tcase_add_test(tc_trim, test_s21_trim_empty_input);
  tcase_add_test(tc_trim, test_s21_trim_null_input);

  suite_add_tcase(s, tc_trim);

  return s;
}
