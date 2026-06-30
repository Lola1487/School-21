#include "test_decimal.h"

/* Test 1: Two zero decimals should be equal (1 should be returned) */
START_TEST(test_is_greater_or_equal_zero_equal) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 2: Positive value with higher scale should be greater than negative
 * value */
START_TEST(test_is_greater_or_equal_positive_vs_negative) {
  s21_decimal val1 = {{1, 2, 3, 655360}};       // Positive, scale 10
  s21_decimal val2 = {{3, 2, 1, -2146828288}};  // Negative, scale 0
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 3: Smaller negative value should not be greater than or equal to larger
 * negative */
START_TEST(test_is_greater_or_equal_negative_comparison) {
  s21_decimal val1 = {{1, 2, 3, -2146828288}};  // Smaller negative value
  s21_decimal val2 = {{3, 2, 1, -2146828288}};  // Larger negative value
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 4: Value with smaller scale should be greater than value with larger
 * scale */
START_TEST(test_is_greater_or_equal_different_scales) {
  s21_decimal val1 = {{1, 2, 3, -2146566144}};  // Negative, scale 5
  s21_decimal val2 = {{3, 2, 1, -2146959360}};  // Negative, scale 7
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 5: Negative value with high scale should not be greater than positive
 * value */
START_TEST(test_is_greater_or_equal_negative_vs_positive) {
  s21_decimal val1 = {{10, 2, 3, -2146566144}};  // Negative, scale 5
  s21_decimal val2 = {{3, 2, 1, 524288}};        // Positive, scale 8
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 6: Identical values should be equal (1 should be returned) */
START_TEST(test_is_greater_or_equal_identical_values) {
  s21_decimal val1 = {{1, 2, 3, 917504}};  // Positive, scale 14
  s21_decimal val2 = {{1, 2, 3, 917504}};  // Positive, scale 14
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* ===== НОВЫЕ ТЕСТЫ ДЛЯ ПОКРЫТИЯ NaN (строка 6) ===== */
/* Test 7: First value is NaN - should return false (0) */
START_TEST(test_is_greater_or_equal_nan_first) {
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 -> NaN
  s21_decimal val2 = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(nan_val, val2), 0);
}
END_TEST

/* Test 8: Second value is NaN - should return false (0) */
START_TEST(test_is_greater_or_equal_nan_second) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 -> NaN
  ck_assert_int_eq(s21_is_greater_or_equal(val1, nan_val), 0);
}
END_TEST

/* Test 9: Both values are NaN - should return false (0) */
START_TEST(test_is_greater_or_equal_nan_both) {
  s21_decimal nan_val1 = {{0, 0, 0, 0x001D0000}};  // scale = 29
  s21_decimal nan_val2 = {{0, 0, 0, 0x001E0000}};  // scale = 30
  ck_assert_int_eq(s21_is_greater_or_equal(nan_val1, nan_val2), 0);
}
END_TEST

Suite *test_is_greater_or_equal(void) {
  Suite *s = suite_create("\033[1;34ms21_is_greater_or_equal\033[0m");
  TCase *tc = tcase_create("is_greater_or_equal_tc");
  tcase_add_test(tc, test_is_greater_or_equal_zero_equal);
  tcase_add_test(tc, test_is_greater_or_equal_positive_vs_negative);
  tcase_add_test(tc, test_is_greater_or_equal_negative_comparison);
  tcase_add_test(tc, test_is_greater_or_equal_different_scales);
  tcase_add_test(tc, test_is_greater_or_equal_negative_vs_positive);
  tcase_add_test(tc, test_is_greater_or_equal_identical_values);
  // Регистрация новых тестов для покрытия строки 6
  tcase_add_test(tc, test_is_greater_or_equal_nan_first);
  tcase_add_test(tc, test_is_greater_or_equal_nan_second);
  tcase_add_test(tc, test_is_greater_or_equal_nan_both);
  suite_add_tcase(s, tc);
  return s;
}
