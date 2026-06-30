#include "test_decimal.h"

/* Test 1: Compare two zero values - should return false (0) since they are
 * equal */
START_TEST(test_is_less_zero_values) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 2: Compare 255 < 256 - should return true (1) */
START_TEST(test_is_less_smaller_low_bits) {
  s21_decimal val1 = {{255, 0, 0, 0}};
  s21_decimal val2 = {{256, 0, 0, 0}};
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 3: Compare 256 < 256 - should return false (0) since values are equal */
START_TEST(test_is_less_equal_values) {
  s21_decimal val1 = {{256, 0, 0, 0}};
  s21_decimal val2 = {{256, 0, 0, 0}};
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 4: Compare 257 < 256 - should return false (0) since 257 is greater */
START_TEST(test_is_less_greater_value) {
  s21_decimal val1 = {{257, 0, 0, 0}};
  s21_decimal val2 = {{256, 0, 0, 0}};
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 5: Compare positive value with negative value - should return false (0)
 */
START_TEST(test_is_less_positive_vs_negative) {
  s21_decimal val1 = {{1, 2, 3, 655360}};                     // Positive value
  s21_decimal val2 = {{3, 2, 1, (unsigned int)-2146828288}};  // Negative value
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 6: Compare two negative values with different magnitudes */
START_TEST(test_is_less_negative_values) {
  s21_decimal val1 = {{1, 2, 3, (unsigned int)-2146828288}};  // Negative value
  s21_decimal val2 = {{3, 2, 1, (unsigned int)-2146828288}};  // Negative value
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 7: Compare values with different scales */
START_TEST(test_is_less_different_scales) {
  s21_decimal val1 = {{1, 2, 3, (unsigned int)-2146566144}};  // Scale 5
  s21_decimal val2 = {{3, 2, 1, (unsigned int)-2146959360}};  // Scale 7
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 8: Compare negative value with scaled positive value */
START_TEST(test_is_less_negative_vs_scaled_positive) {
  s21_decimal val1 = {{10, 2, 3, (unsigned int)-2146566144}};  // Negative
  s21_decimal val2 = {{3, 2, 1, 524288}};                      // Positive
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 9: Compare identical values with same scale - should return false (0) */
START_TEST(test_is_less_identical_values) {
  s21_decimal val1 = {{1, 2, 3, 917504}};
  s21_decimal val2 = {{1, 2, 3, 917504}};
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* ===== НОВЫЕ ТЕСТЫ ДЛЯ ПОКРЫТИЯ NaN (строка 6) ===== */

/* Test 10: First value is NaN - should return false (0) */
START_TEST(test_is_less_nan_first) {
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 -> NaN
  s21_decimal val2 = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(nan_val, val2), 0);
}
END_TEST

/* Test 11: Second value is NaN - should return false (0) */
START_TEST(test_is_less_nan_second) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 -> NaN
  ck_assert_int_eq(s21_is_less(val1, nan_val), 0);
}
END_TEST

/* Test 12: Both values are NaN - should return false (0) */
START_TEST(test_is_less_nan_both) {
  s21_decimal nan_val1 = {{0, 0, 0, 0x001D0000}};  // scale = 29
  s21_decimal nan_val2 = {{0, 0, 0, 0x001E0000}};  // scale = 30
  ck_assert_int_eq(s21_is_less(nan_val1, nan_val2), 0);
}
END_TEST

Suite *test_is_less(void) {
  Suite *s = suite_create("\033[1;34ms21_is_less\033[0m");
  TCase *tc = tcase_create("is_less_tc");
  tcase_add_test(tc, test_is_less_zero_values);
  tcase_add_test(tc, test_is_less_smaller_low_bits);
  tcase_add_test(tc, test_is_less_equal_values);
  tcase_add_test(tc, test_is_less_greater_value);
  tcase_add_test(tc, test_is_less_positive_vs_negative);
  tcase_add_test(tc, test_is_less_negative_values);
  tcase_add_test(tc, test_is_less_different_scales);
  tcase_add_test(tc, test_is_less_negative_vs_scaled_positive);
  tcase_add_test(tc, test_is_less_identical_values);
  // Регистрация новых тестов для покрытия строки 6 (NaN)
  tcase_add_test(tc, test_is_less_nan_first);
  tcase_add_test(tc, test_is_less_nan_second);
  tcase_add_test(tc, test_is_less_nan_both);
  suite_add_tcase(s, tc);
  return s;
}
