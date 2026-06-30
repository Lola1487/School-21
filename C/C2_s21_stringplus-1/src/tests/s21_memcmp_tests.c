#include "s21_test_runner.h"

// Function to assert that two integers are equal
#define CK_ASSERT_INT_EQ(a, b) ck_assert_int_eq((a), (b))

// Test function to check comparison of strings with same length
START_TEST(s21_memcmp_equal_strings) {
  // ARRANGE
  const char *str1 = "hello";  // First string
  const char *str2 = "hello";  // Second string (same as first)

  // ACT
  int std_result = memcmp(str1, str2, 5);      // Standard library comparison
  int s21_result = s21_memcmp(str1, str2, 5);  // Your implementation

  // ASSERT
  CK_ASSERT_INT_EQ(std_result, s21_result);  // Check if results match
}
END_TEST

// Test function to check comparison of strings with different lengths
START_TEST(s21_memcmp_different_length_strings) {
  // ARRANGE
  const char *str1 = "hello";       // Shorter string
  const char *str2 = "helloworld";  // Longer string

  // ACT
  // Compare only the shorter string's length (5 characters)
  int std_result = memcmp(str1, str2, strlen(str1));
  int s21_result = s21_memcmp(str1, str2, strlen(str1));

  // ASSERT
  CK_ASSERT_INT_EQ(std_result, s21_result);  // Check if results match
}
END_TEST

// Test function to check comparison of strings with different character order
START_TEST(s21_memcmp_different_order_strings) {
  // ARRANGE
  const char *str1 = "abc";  // String with ordered characters
  const char *str2 = "cab";  // String with different character order

  // ACT
  int std_result = memcmp(str1, str2, 3);  // Compare up to 3 characters
  int s21_result = s21_memcmp(str1, str2, 3);

  // ASSERT
  CK_ASSERT_INT_EQ(std_result, s21_result);  // Check if results match
}
END_TEST

// Test function to check comparison of empty strings
START_TEST(s21_memcmp_empty_strings) {
  // ARRANGE
  const char *str1 = "";  // Empty string
  const char *str2 = "";  // Another empty string

  // ACT
  int std_result = memcmp(str1, str2, 0);  // Compare no characters
  int s21_result = s21_memcmp(str1, str2, 0);

  // ASSERT
  CK_ASSERT_INT_EQ(std_result, s21_result);  // Check if results match
}
END_TEST

// Test function to check comparison of strings with different sizes
START_TEST(s21_memcmp_different_sizes_strings) {
  // ARRANGE
  const char *str1 = "abcd";  // Longer string
  const char *str2 = "abc";   // Shorter string

  // ACT
  int std_result = memcmp(
      str1, str2, strlen(str2));  // Compare up to shorter string's length
  int s21_result = s21_memcmp(str1, str2, strlen(str2));

  // ASSERT
  CK_ASSERT_INT_EQ(std_result, s21_result);  // Check if results match
}
END_TEST

// Create test suite for s21_memcmp function
Suite *tests_for_memcmp(void) {
  Suite *s;
  TCase *tc_memcmp;

  s = suite_create("memcmp_tests");       // Create test suite
  tc_memcmp = tcase_create("memcmp_tc");  // Create test case

  tcase_add_test(tc_memcmp, s21_memcmp_equal_strings);  // Add test cases
  tcase_add_test(tc_memcmp, s21_memcmp_different_length_strings);
  tcase_add_test(tc_memcmp, s21_memcmp_different_order_strings);
  tcase_add_test(tc_memcmp, s21_memcmp_empty_strings);
  tcase_add_test(tc_memcmp, s21_memcmp_different_sizes_strings);

  suite_add_tcase(s, tc_memcmp);  // Add test case to suite

  return s;  // Return the created test suite
}
