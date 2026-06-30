#include "test_decimal.h"

START_TEST(test_from_int_to_decimal_positive) {
  int src = 123456;
  s21_decimal dst = {{0}};
  int res = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(dst.bits[0], 123456);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_negative) {
  int src = -123456;
  s21_decimal dst = {{0}};
  int res = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(dst.bits[0], 123456);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0x80000000);  // Sign bit set
}
END_TEST

START_TEST(test_from_int_to_decimal_zero) {
  int src = 0;
  s21_decimal dst = {{0}};
  int res = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_max) {
  int src = 2147483647;
  s21_decimal dst = {{0}};
  int res = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_min) {
  int src = -2147483648;
  s21_decimal dst = {{0}};
  int res = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *test_from_int_to_decimal(void) {
  Suite *s = suite_create("\033[1;36ms21_from_int_to_decimal\033[0m");
  TCase *tc_core = tcase_create("from_int_to_decimal_tc");
  tcase_add_test(tc_core, test_from_int_to_decimal_positive);
  tcase_add_test(tc_core, test_from_int_to_decimal_negative);
  tcase_add_test(tc_core, test_from_int_to_decimal_zero);
  tcase_add_test(tc_core, test_from_int_to_decimal_max);
  tcase_add_test(tc_core, test_from_int_to_decimal_min);
  suite_add_tcase(s, tc_core);
  return s;
}
