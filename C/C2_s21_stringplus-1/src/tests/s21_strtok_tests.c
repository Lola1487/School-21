#include "s21_test_runner.h"

START_TEST(s21_strtok_multiple_delimiters) {
  // ARRANGE
  char s21_input[] = "Welcome!to&the!coding)world(";
  const char delimiters[] = "!&()";

  char std_input[] = "Welcome!to&the!coding)world(";
  const char std_delimiters[] = "!&()";

  // ACT & ASSERT
  // Loop through all tokens and compare results from both functions
  char *s21_token = s21_strtok(s21_input, delimiters);
  char *std_token = strtok(std_input, std_delimiters);

  while (s21_token != s21_NULL) {
    // Assert that each token matches between implementations
    ck_assert_str_eq(s21_token, std_token);

    // Get next tokens
    s21_token = s21_strtok(s21_NULL, delimiters);
    std_token = strtok(s21_NULL, std_delimiters);
  }
}
END_TEST

/**
 * @brief Test tokenizing a string with delimiters at different positions
 *
 * Verifies s21_strtok behavior with a string containing delimiters at
 * beginning, middle, and end positions.
 */
START_TEST(s21_strtok_delimiter_positions) {
  // ARRANGE
  char s21_input[] = "Morning!sunshine&have!great)day";
  const char delimiters[] = "!&)";

  char std_input[] = "Morning!sunshine&have!great)day";
  const char std_delimiters[] = "!&)";

  // ACT & ASSERT
  char *s21_token = s21_strtok(s21_input, delimiters);
  char *std_token = strtok(std_input, std_delimiters);

  while (s21_token != s21_NULL) {
    ck_assert_str_eq(s21_token, std_token);
    s21_token = s21_strtok(s21_NULL, delimiters);
    std_token = strtok(s21_NULL, std_delimiters);
  }
}
END_TEST

/**
 * @brief Test tokenizing an empty string
 *
 * Tests the behavior of s21_strtok with an empty input string.
 */
START_TEST(s21_strtok_empty_string) {
  // ARRANGE
  char s21_input[] = "";
  const char delimiters[] = "!&)";

  char std_input[] = "";
  const char std_delimiters[] = "!&)";

  // ACT
  char *s21_token = s21_strtok(s21_input, delimiters);
  char *std_token = strtok(std_input, std_delimiters);

  // ASSERT
  ck_assert_ptr_eq(s21_token, std_token);  // Both should return NULL
}
END_TEST

/**
 * @brief Test tokenizing a string containing only delimiters
 *
 * Verifies s21_strtok behavior when the input string contains only delimiter
 * characters.
 */
START_TEST(s21_strtok_only_delimiters) {
  // ARRANGE
  char s21_input[] = "! & )";
  const char delimiters[] = "!&)";

  char std_input[] = "! & )";
  const char std_delimiters[] = "!&)";

  // ACT
  char *s21_token = s21_strtok(s21_input, delimiters);
  char *std_token = strtok(std_input, std_delimiters);

  // ASSERT
  ck_assert_str_eq(s21_token, std_token);
}
END_TEST

/**
 * @brief Test with an empty delimiter string
 *
 * Tests tokenizing a string when the delimiter string is empty (contains only a
 * null terminator).
 */
START_TEST(s21_strtok_empty_delimiter) {
  // ARRANGE
  char s21_input[] = "characters";
  const char delimiters[] = {'\0'};

  char std_input[] = "characters";
  const char std_delimiters[] = {'\0'};

  // ACT & ASSERT
  char *s21_token = s21_strtok(s21_input, delimiters);
  char *std_token = strtok(std_input, std_delimiters);

  while (s21_token != s21_NULL) {
    ck_assert_str_eq(s21_token, std_token);
    s21_token = s21_strtok(s21_NULL, delimiters);
    std_token = strtok(s21_NULL, std_delimiters);
  }
}
END_TEST

/**
 * @brief Test with a string that doesn't contain any delimiters
 *
 * Verifies behavior when the input string doesn't contain any of the specified
 * delimiters.
 */
START_TEST(s21_strtok_no_delimiters_present) {
  // ARRANGE
  char s21_input[] = "NoDelimitersHere";
  const char delimiters[] = "!&)";

  char std_input[] = "NoDelimitersHere";
  const char std_delimiters[] = "!&)";

  // ACT & ASSERT
  char *s21_token = s21_strtok(s21_input, delimiters);
  char *std_token = strtok(std_input, std_delimiters);

  while (s21_token != s21_NULL) {
    ck_assert_str_eq(s21_token, std_token);
    s21_token = s21_strtok(s21_NULL, delimiters);
    std_token = strtok(s21_NULL, std_delimiters);
  }
}
END_TEST

/**
 * @brief Test with complex string containing multiple delimiter types
 *
 * Tests tokenizing a complex string with various delimiter characters at
 * different positions.
 */
START_TEST(s21_strtok_complex_string) {
  // ARRANGE
  char s21_input[] = "Apple$!Orange@!!Banana&&)Grape";
  const char delimiters[] = "!&)";

  char std_input[] = "Apple$!Orange@!!Banana&&)Grape";
  const char std_delimiters[] = "!&)";

  // ACT & ASSERT
  char *s21_token = s21_strtok(s21_input, delimiters);
  char *std_token = strtok(std_input, std_delimiters);

  while (s21_token != s21_NULL) {
    ck_assert_str_eq(s21_token, std_token);
    s21_token = s21_strtok(s21_NULL, delimiters);
    std_token = strtok(s21_NULL, std_delimiters);
  }
}
END_TEST

/**
 * @brief Test with NULL delimiter
 *
 * Tests s21_strtok's behavior when called with a NULL delimiter.
 */
START_TEST(s21_strtok_null_delimiter) {
  // ARRANGE
  char test_string[] = "Hello, World!";

  // ACT
  char *result = s21_strtok(test_string, s21_NULL);

  // ASSERT
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

/**
 * @brief Test with NULL string and valid delimiter
 *
 * Tests calling s21_strtok with NULL string on first call (not continuation).
 */
START_TEST(s21_strtok_null_string) {
  // ARRANGE
  const char *delimiter = "!";

  // ACT
  char *result = s21_strtok(s21_NULL, delimiter);

  // ASSERT
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

/**
 * @brief Test with empty string and valid delimiter
 *
 * Tests s21_strtok's behavior when the input string is empty.
 */
START_TEST(s21_strtok_empty_string_check) {
  // ARRANGE
  char test_string[] = "";
  const char delimiters[] = "!&)";

  // ACT
  char *result = s21_strtok(test_string, delimiters);

  // ASSERT
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

/**
 * @brief Test with multiple calls and continuations
 *
 * Tests s21_strtok's ability to maintain state across multiple continuation
 * calls.
 */
START_TEST(s21_strtok_multiple_continuations) {
  // ARRANGE
  char s21_input[] = "5313a57bfb74565";
  char std_input[] = "5313a57bfb74565";
  const char delimiters[] = "7";

  // ACT - First token
  strtok(std_input, delimiters);
  s21_strtok(s21_input, delimiters);

  // ACT - Second token (first continuation)
  strtok(s21_NULL, delimiters);
  s21_strtok(s21_NULL, delimiters);

  // ACT - Third token (second continuation)
  char *correct = strtok(s21_NULL, delimiters);
  char *s21_result = s21_strtok(s21_NULL, delimiters);

  // ASSERT
  ck_assert_str_eq(correct, s21_result);
}
END_TEST

/**
 * @brief Test with NULL string in continuation mode
 *
 * Tests calling s21_strtok with NULL for both parameters when no previous call
 * was made.
 */
START_TEST(s21_strtok_null_continuation) {
  // ARRANGE - No prior call setup

  // ACT
  char *s21_result = s21_strtok(s21_NULL, "!543");

  // ASSERT
  ck_assert_ptr_null(s21_result);
}
END_TEST

/**
 * @brief Creates a test suite for s21_strtok function
 *
 * @return Suite* - The test suite containing all test cases for s21_strtok
 */
Suite *tests_for_strtok(void) {
  Suite *s;
  TCase *tc_strtok;
  s = suite_create("strtok_tests");
  tc_strtok = tcase_create("strtok_tc");

  // Add all test cases to the test case
  tcase_add_test(tc_strtok, s21_strtok_multiple_delimiters);
  tcase_add_test(tc_strtok, s21_strtok_delimiter_positions);
  tcase_add_test(tc_strtok, s21_strtok_empty_string);
  tcase_add_test(tc_strtok, s21_strtok_only_delimiters);
  tcase_add_test(tc_strtok, s21_strtok_empty_delimiter);
  tcase_add_test(tc_strtok, s21_strtok_no_delimiters_present);
  tcase_add_test(tc_strtok, s21_strtok_complex_string);
  tcase_add_test(tc_strtok, s21_strtok_null_delimiter);
  tcase_add_test(tc_strtok, s21_strtok_null_string);
  tcase_add_test(tc_strtok, s21_strtok_empty_string_check);
  tcase_add_test(tc_strtok, s21_strtok_multiple_continuations);
  tcase_add_test(tc_strtok, s21_strtok_null_continuation);

  // Add the test case to the suite
  suite_add_tcase(s, tc_strtok);

  return s;
}
