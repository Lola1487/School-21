// #include "../s21_string.h"
#include "s21_test_runner.h"

START_TEST(test_strchr_found_middle) {
  // Arrange
  const char str[] = "Nice day!";  // Test string with Latin characters
  char c = 'd';                    // Target character to find

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when the target character is
 * at the beginning of the string.
 */
START_TEST(test_strchr_found_start) {
  // Arrange
  const char str[] = "Nice day!";
  char c = 'N';  // First character of the string

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when the target character is
 * at the end of the string.
 */
START_TEST(test_strchr_found_end) {
  // Arrange
  const char str[] = "Nice day!";
  char c = '!';  // Last character of the string

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when the target character does
 * not exist in the string.
 */
START_TEST(test_strchr_not_found) {
  // Arrange
  const char str[] = "Nice day!";
  char c = 'z';  // Character that is absent in the string

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when searching for the null
 * terminator ('\0').
 */
START_TEST(test_strchr_find_null) {
  // Arrange
  const char str[] = "Nice day!";
  char c = '\0';  // Null terminator character

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() with an empty string.
 */
START_TEST(test_strchr_empty_string) {
  // Arrange
  const char str[] = "";  // Empty string
  char c = 'A';           // Any character

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() with a long string.
 */
START_TEST(test_strchr_long_string) {
  // Arrange
  char str[1000];
  for (int i = 0; i < 999; i++) {
    str[i] = (i == 500) ? 'x' : 'a';  // Fill the string with random characters
  }
  str[999] = '\0';  // Terminate the string with null character

  char c = 'x';  // Target character to find

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when multiple occurrences of
 * the same character are present.
 */
START_TEST(test_strchr_multiple_occurrences) {
  // Arrange
  const char str[] =
      "aaaaaaa";  // String with multiple occurrences of the same character
  char c = 'a';   // Target character to find

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when the string consists
 * entirely of the target character.
 */
START_TEST(test_strchr_only_target) {
  // Arrange
  const char str[] =
      "aaaaaaa";  // String consisting only of the target character
  char c = 'a';   // Target character to find

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() with high-value ASCII
 * characters.
 */
START_TEST(test_strchr_high_ascii) {
  // Arrange
  const char str[] =
      "Bad \x7F day";        // String containing a high-value ASCII character
  unsigned char c = '\x7F';  // High-value ASCII character to find

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when the last character of the
 * string is the target.
 */
START_TEST(test_strchr_last_character) {
  // Arrange
  const char str[] = "Good!";
  char c = '!';  // Last character of the string

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when the target character is
 * not found in a string with spaces.
 */
START_TEST(test_strchr_not_found_with_spaces) {
  // Arrange
  const char str[] = "    ";  // String with spaces only
  char c = 'a';               // Character that should not be found

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @test Checks the functionality of s21_strchr() when the target character is a
 * space.
 */
START_TEST(test_strchr_space) {
  // Arrange
  const char str[] = "This is a simple sentence.";  // String with spaces
  char c = ' ';                                     // Space character to find

  // Act
  char *result = s21_strchr(str, c);  // Call our implementation

  // Assert
  ck_assert_ptr_eq(
      result, strchr(str, c));  // Compare result with standard library function
}
END_TEST

/**
 * @brief Creates a test suite for testing the s21_strchr() function.
 * @return Pointer to the created test suite.
 */
Suite *tests_for_strchr(void) {
  Suite *s;
  TCase *tc_strchr;
  s = suite_create("strchr_tests");       // Create new test suite
  tc_strchr = tcase_create("tc_strchr");  // Create new test case group

  // Add individual tests to the test case group
  tcase_add_test(tc_strchr, test_strchr_found_middle);
  tcase_add_test(tc_strchr, test_strchr_found_start);
  tcase_add_test(tc_strchr, test_strchr_found_end);
  tcase_add_test(tc_strchr, test_strchr_not_found);
  tcase_add_test(tc_strchr, test_strchr_find_null);
  tcase_add_test(tc_strchr, test_strchr_empty_string);
  tcase_add_test(tc_strchr, test_strchr_long_string);
  tcase_add_test(tc_strchr, test_strchr_multiple_occurrences);
  tcase_add_test(tc_strchr, test_strchr_only_target);
  tcase_add_test(tc_strchr, test_strchr_high_ascii);
  tcase_add_test(tc_strchr, test_strchr_last_character);
  tcase_add_test(tc_strchr, test_strchr_not_found_with_spaces);
  tcase_add_test(tc_strchr, test_strchr_space);

  suite_add_tcase(s, tc_strchr);  // Add test case group to the test suite

  return s;  // Return pointer to the created test suite
}

/** @} */  // End of the STRCHR_Tests group
