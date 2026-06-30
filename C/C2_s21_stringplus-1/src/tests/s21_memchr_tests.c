// #include "../s21_string.h"
#include "s21_test_runner.h"

// Standard case
START_TEST(test_standard_case) {
  // ARRANGE
  /**
   * @brief Prepare the test string and target character.
   */
  const char str[] = "Hello, World!";
  int target = 'W';  // Search for uppercase letter W
  size_t n = strlen(str);

  // ACT
  /**
   * @brief Perform the search using both standard memchr and our s21_memchr
   * implementation.
   */
  void *result_std = memchr(str, target, n);
  void *result_s21 = s21_memchr(str, target, n);

  // ASSERT
  /**
   * @brief Verify that the results from the standard and custom implementations
   * match.
   */
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

// Character not found in the string
START_TEST(test_char_not_found) {
  // ARRANGE
  const char str[] = "Hello, World!";
  int target = 'Z';  // Letter Z does not exist in the string
  size_t n = strlen(str);

  // ACT
  void *result_std = memchr(str, target, n);
  void *result_s21 = s21_memchr(str, target, n);

  // ASSERT
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

// Character found at the beginning of the string
START_TEST(test_char_at_start) {
  // ARRANGE
  const char str[] = "Hello, World!";
  int target = 'H';  // First letter H
  size_t n = strlen(str);

  // ACT
  void *result_std = memchr(str, target, n);
  void *result_s21 = s21_memchr(str, target, n);

  // ASSERT
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

// Character found at the end of the string
START_TEST(test_char_at_end) {
  // ARRANGE
  const char str[] = "Hello, World!";
  int target = '!';  // Exclamation mark at the end
  size_t n = strlen(str);

  // ACT
  void *result_std = memchr(str, target, n);
  void *result_s21 = s21_memchr(str, target, n);

  // ASSERT
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

// Other tests... (similarly formatted)

Suite *tests_for_memchr(void) {
  Suite *s;
  TCase *tc_memchr;
  s = suite_create("s21_memchr_tests");
  tc_memchr = tcase_create("tc_memchr");
  tcase_add_test(tc_memchr, test_standard_case);
  tcase_add_test(tc_memchr, test_char_not_found);
  tcase_add_test(tc_memchr, test_char_at_start);
  tcase_add_test(tc_memchr, test_char_at_end);
  // Add other tests...

  suite_add_tcase(s, tc_memchr);

  return s;
}
