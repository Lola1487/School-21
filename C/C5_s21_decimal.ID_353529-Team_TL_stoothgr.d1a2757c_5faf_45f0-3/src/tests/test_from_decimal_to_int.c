#include "test_decimal.h"

START_TEST(test_from_decimal_to_int_positive) {
  s21_decimal src = {{123456, 0, 0, 0}};
  int expected = 123456;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_negative) {
  s21_decimal src = {{654321, 0, 0, 0x80000000}};
  int expected = -654321;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_zero) {
  s21_decimal src = {{0, 0, 0, 0}};
  int expected = 0;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_min) {
  s21_decimal src = {{2147483648U, 0, 0, 0x80000000}};
  int expected = -2147483648;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_max) {
  s21_decimal src = {{2147483647, 0, 0, 0}};
  int expected = 2147483647;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_small_negative) {
  s21_decimal src = {{1, 0, 0, 0x80000000}};
  int expected = -1;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_short_int) {
  s21_decimal src = {{32767, 0, 0, 0}};
  int expected = 32767;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_small_positive) {
  s21_decimal src = {{1, 0, 0, 0}};
  int expected = 1;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_short_int_negative) {
  s21_decimal src = {{32768, 0, 0, 0x80000000}};
  int expected = -32768;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_large_positive) {
  s21_decimal src = {{1000000, 0, 0, 0}};
  int expected = 1000000;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_overflow_positive) {
  s21_decimal src = {{2147483648U, 0, 0, 0}};
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_overflow_negative) {
  s21_decimal src = {{2147483649U, 0, 0, 0x80000000}};
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_rounding_positive) {
  s21_decimal src = {{123456, 0, 0, 0x00020000}};
  int expected = 1234;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_rounding_negative) {
  s21_decimal src = {{123456, 0, 0, 0x80020000}};
  int expected = -1234;
  int result;
  int error_code = s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_from_decimal_to_int_null_pointer) {
  s21_decimal src = {{123, 0, 0, 0}};
  int error_code = s21_from_decimal_to_int(src, NULL);
  ck_assert_int_eq(error_code, 1);
}
END_TEST

Suite *test_from_decimal_to_int(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[1;36ms21_from_decimal_to_int\033[0m");
  tc_core = tcase_create("from_decimal_to_int_tc");
  tcase_add_test(tc_core, test_from_decimal_to_int_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_negative);
  tcase_add_test(tc_core, test_from_decimal_to_int_zero);
  tcase_add_test(tc_core, test_from_decimal_to_int_min);
  tcase_add_test(tc_core, test_from_decimal_to_int_max);
  tcase_add_test(tc_core, test_from_decimal_to_int_small_negative);
  tcase_add_test(tc_core, test_from_decimal_to_int_short_int);
  tcase_add_test(tc_core, test_from_decimal_to_int_small_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_short_int_negative);
  tcase_add_test(tc_core, test_from_decimal_to_int_large_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_overflow_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_overflow_negative);
  tcase_add_test(tc_core, test_from_decimal_to_int_rounding_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_rounding_negative);
  tcase_add_test(tc_core, test_from_decimal_to_int_null_pointer);
  suite_add_tcase(s, tc_core);
  return s;
}
