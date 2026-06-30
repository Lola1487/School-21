#include <float.h>
#include <math.h>

#include "test_decimal.h"

START_TEST(test_from_decimal_to_float_positive) {
  s21_decimal src = {{0x40000000, 0, 0, 0}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, 1073741824.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative) {
  s21_decimal src = {{0x40000000, 0, 0, 0x80000000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, -1073741824.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_zero) {
  s21_decimal src = {{0, 0, 0, 0}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_with_scale) {
  s21_decimal src = {{0x00000064, 0, 0, 0x00020000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, 1.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_null_ptr) {
  s21_decimal src = {{0x40000000, 0, 0, 0}};
  int result = s21_from_decimal_to_float(src, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_max_value) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert(dst > 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_min_scale) {
  s21_decimal src = {{1, 0, 0, 0x001C0000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_decimal_to_float_underflow_check) {
  s21_decimal src = {{1, 0, 0, 0x001D0000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative_scale) {
  s21_decimal src = {{100, 0, 0, 0x80020000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, -1.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_large_no_scale) {
  s21_decimal src = {{0x80000000, 0x40000000, 0x20000000, 0}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert(dst > 0.0f);
}
END_TEST

Suite *test_from_decimal_to_float(void) {
  Suite *s = suite_create("\033[1;32ms21_from_decimal_to_float\033[0m");
  TCase *tc = tcase_create("from_decimal_to_float_tc");

  tcase_add_test(tc, test_from_decimal_to_float_positive);
  tcase_add_test(tc, test_from_decimal_to_float_negative);
  tcase_add_test(tc, test_from_decimal_to_float_zero);
  tcase_add_test(tc, test_from_decimal_to_float_with_scale);
  tcase_add_test(tc, test_from_decimal_to_float_null_ptr);
  tcase_add_test(tc, test_from_decimal_to_float_max_value);
  tcase_add_test(tc, test_from_decimal_to_float_min_scale);
  tcase_add_test(tc, test_from_decimal_to_float_underflow_check);
  tcase_add_test(tc, test_from_decimal_to_float_negative_scale);
  tcase_add_test(tc, test_from_decimal_to_float_large_no_scale);

  suite_add_tcase(s, tc);
  return s;
}
