#include "test_decimal.h"

/* Test 1: Both decimals are zero - should be equal regardless of sign */
START_TEST(test_is_equal_both_zeros) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 2: Different values with same sign but different mantissas - should not
 * be equal */
START_TEST(test_is_equal_different_mantissas_same_sign) {
  s21_decimal val1 = {{1, 2, 3, 655360}};  // Positive value 1
  s21_decimal val2 = {
      {3, 2, 1, -2146828288}};  // Negative value 2 (different sign)
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 3: Different values with same negative sign - should not be equal */
START_TEST(test_is_equal_different_values_same_negative_sign) {
  s21_decimal val1 = {{1, 2, 3, -2146828288}};  // Negative value 1
  s21_decimal val2 = {{3, 2, 1, -2146828288}};  // Negative value 2
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 4: Different values with different scales and signs - should not be
 * equal */
START_TEST(test_is_equal_different_scales_and_signs) {
  s21_decimal val1 = {{1, 2, 3, -2146566144}};  // Negative with scale
  s21_decimal val2 = {{3, 2, 1, -2146959360}};  // Negative with different scale
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 5: Different values with opposite signs - should not be equal */
START_TEST(test_is_equal_opposite_signs_different_values) {
  s21_decimal val1 = {{10, 2, 3, -2146566144}};  // Negative value
  s21_decimal val2 = {{3, 2, 1, 524288}};        // Positive value
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

/* Test 6: Identical values with same scale - should be equal */
START_TEST(test_is_equal_identical_values) {
  s21_decimal val1 = {{1, 2, 3, 917504}};  // Specific value with scale
  s21_decimal val2 = {{1, 2, 3, 917504}};  // Same value and scale
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* Test 7: Zero with negative sign vs zero without sign - should be equal */
START_TEST(test_is_equal_signed_zero_vs_unsigned_zero) {
  s21_decimal val1 = {{0, 0, 0, -2147418112}};  // Negative zero
  s21_decimal val2 = {{0, 0, 0, 0}};            // Positive zero
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

/* ===== НОВЫЕ ТЕСТЫ ДЛЯ ПОКРЫТИЯ NaN (строка 6) ===== */

/* Test 8: First value is NaN - should return false (0) */
START_TEST(test_is_equal_nan_first) {
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 -> NaN
  s21_decimal val2 = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(nan_val, val2), 0);
}
END_TEST

/* Test 9: Second value is NaN - should return false (0) */
START_TEST(test_is_equal_nan_second) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 -> NaN
  ck_assert_int_eq(s21_is_equal(val1, nan_val), 0);
}
END_TEST

/* Test 10: Both values are NaN - should return false (0) */
START_TEST(test_is_equal_nan_both) {
  s21_decimal nan_val1 = {{0, 0, 0, 0x001D0000}};  // scale = 29
  s21_decimal nan_val2 = {{0, 0, 0, 0x001E0000}};  // scale = 30
  ck_assert_int_eq(s21_is_equal(nan_val1, nan_val2), 0);
}
END_TEST

Suite *test_is_equal(void) {
  Suite *s = suite_create("\033[1;34ms21_is_equal\033[0m");
  TCase *tc = tcase_create("is_equal_tc");
  tcase_add_test(tc, test_is_equal_both_zeros);
  tcase_add_test(tc, test_is_equal_different_mantissas_same_sign);
  tcase_add_test(tc, test_is_equal_different_values_same_negative_sign);
  tcase_add_test(tc, test_is_equal_different_scales_and_signs);
  tcase_add_test(tc, test_is_equal_opposite_signs_different_values);
  tcase_add_test(tc, test_is_equal_identical_values);
  tcase_add_test(tc, test_is_equal_signed_zero_vs_unsigned_zero);
  // Регистрация новых тестов для покрытия строки 6 (NaN)
  tcase_add_test(tc, test_is_equal_nan_first);
  tcase_add_test(tc, test_is_equal_nan_second);
  tcase_add_test(tc, test_is_equal_nan_both);
  suite_add_tcase(s, tc);
  return s;
}
