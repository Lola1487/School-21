#include "test_decimal.h"

/* Test 1: Both decimals are zero - should return true (1) since 0 <= 0 */
START_TEST(test_is_less_or_equal_both_zero) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 2: First value is smaller than second - should return true (1) */
START_TEST(test_is_less_or_equal_first_smaller) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 3: Both values are equal - should return true (1) */
START_TEST(test_is_less_or_equal_equal_values) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 4: First value is larger than second - should return false (0) */
START_TEST(test_is_less_or_equal_first_larger) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 5: Complex comparison with different signs and values */
START_TEST(test_is_less_or_equal_complex_signs) {
  s21_decimal val1 = {{1, 2, 3, 655360}};       // Positive value
  s21_decimal val2 = {{3, 2, 1, -2146828288}};  // Negative value
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 6: Both negative values, first is numerically smaller */
START_TEST(test_is_less_or_equal_negative_values) {
  s21_decimal val1 = {{1, 2, 3, -2146828288}};  // Negative value
  s21_decimal val2 = {{3, 2, 1, -2146828288}};  // Negative value
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 7: Values with different scales */
START_TEST(test_is_less_or_equal_different_scales) {
  s21_decimal val1 = {{1, 2, 3, -2146566144}};  // Scale 5, negative
  s21_decimal val2 = {{3, 2, 1, -2146959360}};  // Scale 7, negative
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 8: Mixed signs with different scales */
START_TEST(test_is_less_or_equal_mixed_signs_scales) {
  s21_decimal val1 = {{10, 2, 3, -2146566144}};  // Negative, scale 5
  s21_decimal val2 = {{3, 2, 1, 524288}};        // Positive, scale 5
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 9: Identical complex values - should return true (1) */
START_TEST(test_is_less_or_equal_identical_complex) {
  s21_decimal val1 = {{1, 2, 3, 917504}};  // Scale 5
  s21_decimal val2 = {{1, 2, 3, 917504}};  // Scale 5
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* ===== НОВЫЕ ТЕСТЫ ДЛЯ ПОКРЫТИЯ NaN (строка 6) ===== */
/* Test 10: First value is NaN - should return false (0) */
START_TEST(test_is_less_or_equal_nan_first) {
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 -> NaN
  s21_decimal val2 = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(nan_val, val2), 0);
}
END_TEST

/* Test 11: Second value is NaN - should return false (0) */
START_TEST(test_is_less_or_equal_nan_second) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 -> NaN
  ck_assert_int_eq(s21_is_less_or_equal(val1, nan_val), 0);
}
END_TEST

/* Test 12: Both values are NaN - should return false (0) */
START_TEST(test_is_less_or_equal_nan_both) {
  s21_decimal nan_val1 = {{0, 0, 0, 0x001D0000}};  // scale = 29
  s21_decimal nan_val2 = {{0, 0, 0, 0x001E0000}};  // scale = 30
  ck_assert_int_eq(s21_is_less_or_equal(nan_val1, nan_val2), 0);
}
END_TEST

Suite *test_is_less_or_equal(void) {
  Suite *s = suite_create("\033[1;34ms21_is_less_or_equal\033[0m");
  TCase *tc = tcase_create("is_less_or_equal_tc");
  tcase_add_test(tc, test_is_less_or_equal_both_zero);
  tcase_add_test(tc, test_is_less_or_equal_first_smaller);
  tcase_add_test(tc, test_is_less_or_equal_equal_values);
  tcase_add_test(tc, test_is_less_or_equal_first_larger);
  tcase_add_test(tc, test_is_less_or_equal_complex_signs);
  tcase_add_test(tc, test_is_less_or_equal_negative_values);
  tcase_add_test(tc, test_is_less_or_equal_different_scales);
  tcase_add_test(tc, test_is_less_or_equal_mixed_signs_scales);
  tcase_add_test(tc, test_is_less_or_equal_identical_complex);
  // Регистрация новых тестов для покрытия строки 6
  tcase_add_test(tc, test_is_less_or_equal_nan_first);
  tcase_add_test(tc, test_is_less_or_equal_nan_second);
  tcase_add_test(tc, test_is_less_or_equal_nan_both);
  suite_add_tcase(s, tc);
  return s;
}
