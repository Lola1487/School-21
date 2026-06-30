#include <float.h>
#include <math.h>

#include "../arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"
#include "test_decimal.h"

// Явное объявление функции для устранения ошибки implicit declaration
int s21_is_zero(s21_decimal value);

/* Test 1: Convert negative fractional float with specific precision */
START_TEST(test_from_float_negative_fractional_val1) {
  s21_decimal expected = {{2343453, 0, 0, 0}};
  s21_set_scale(&expected, 7);
  s21_set_sign(&expected, 1);
  float val = -0.2343453f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 2: Convert positive fractional float with mixed integer and decimal
 * parts */
START_TEST(test_from_float_positive_fractional_val2) {
  s21_decimal expected = {{1272343, 0, 0, 0}};
  s21_set_scale(&expected, 4);
  float val = 127.2343f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 3: Convert large positive integer float to decimal */
START_TEST(test_from_float_to_decimal_positive) {
  s21_decimal expected = {{2343453, 0, 0, 0}};
  float val = 2343453.0f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 4: Convert large negative integer float to decimal */
START_TEST(test_from_float_to_decimal_negative) {
  s21_decimal expected = {{2343453, 0, 0, 0}};
  s21_set_sign(&expected, 1);
  float val = -2343453.0f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 5: Convert very small positive float to decimal */
START_TEST(test_from_float_to_decimal_small_positive) {
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_set_scale(&expected, 6);
  float val = 0.000001f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 6: Convert positive fractional float to decimal */
START_TEST(test_from_float_to_decimal_fractional) {
  s21_decimal expected = {{123456, 0, 0, 0}};
  s21_set_scale(&expected, 6);
  float val = 0.123456f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 7: Convert negative fractional float to decimal */
START_TEST(test_from_float_to_decimal_negative_fractional) {
  s21_decimal expected = {{123456, 0, 0, 0}};
  s21_set_scale(&expected, 6);
  s21_set_sign(&expected, 1);
  float val = -0.123456f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 8: Convert common fractional value (1.5) to decimal */
START_TEST(test_from_float_to_decimal_one_point_five) {
  s21_decimal expected = {{15, 0, 0, 0}};
  s21_set_scale(&expected, 1);
  float val = 1.5f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 9: Convert extremely small negative float to decimal */
START_TEST(test_from_float_to_decimal_very_small_negative) {
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_set_scale(&expected, 10);
  s21_set_sign(&expected, 1);
  float val = -1.0e-10f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 10: Test conversion of positive infinity should return error */
START_TEST(test_from_float_to_decimal_infinity) {
  float val = 1.0f / 0.0f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 1);
}
END_TEST

/* Test 11: Test conversion of negative infinity should return error */
START_TEST(test_from_float_to_decimal_negative_infinity) {
  float val = -1.0f / 0.0f;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 1);
}
END_TEST

/* Test 12: Test conversion of NaN value should return error */
START_TEST(test_from_float_to_decimal_nan) {
  float val = NAN;
  s21_decimal result = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &result);
  ck_assert_int_eq(error_code, 1);
}
END_TEST

/* Test 13: Test conversion of 0.0f (Covers line 12-14 in
 * s21_from_float_to_decimal.c) */
START_TEST(test_from_float_to_decimal_zero) {
  float val = 0.0f;
  s21_decimal dst = {{0, 0, 0, 0}};
  int error_code = s21_from_float_to_decimal(val, &dst);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(s21_is_zero(dst), 1);
}
END_TEST

/* Create test suite */
Suite *test_from_float_to_decimal(void) {
  Suite *s = suite_create("\033[1;36ms21_from_float_to_decimal\033[0m");
  TCase *tc_core = tcase_create("from_float_to_decimal_tc");
  tcase_add_test(tc_core, test_from_float_negative_fractional_val1);
  tcase_add_test(tc_core, test_from_float_positive_fractional_val2);
  tcase_add_test(tc_core, test_from_float_to_decimal_positive);
  tcase_add_test(tc_core, test_from_float_to_decimal_negative);
  tcase_add_test(tc_core, test_from_float_to_decimal_small_positive);
  tcase_add_test(tc_core, test_from_float_to_decimal_fractional);
  tcase_add_test(tc_core, test_from_float_to_decimal_negative_fractional);
  tcase_add_test(tc_core, test_from_float_to_decimal_one_point_five);
  tcase_add_test(tc_core, test_from_float_to_decimal_very_small_negative);
  tcase_add_test(tc_core, test_from_float_to_decimal_infinity);
  tcase_add_test(tc_core, test_from_float_to_decimal_negative_infinity);
  tcase_add_test(tc_core, test_from_float_to_decimal_nan);
  tcase_add_test(tc_core,
                 test_from_float_to_decimal_zero);  // Регистрация нового теста
  suite_add_tcase(s, tc_core);
  return s;
}
