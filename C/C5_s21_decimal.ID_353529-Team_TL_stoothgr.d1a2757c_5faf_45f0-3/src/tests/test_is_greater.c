#include "test_decimal.h"

START_TEST(test_is_greater_zero_equal) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(test_is_greater_smaller_positive) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(test_is_greater_equal_values) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(test_is_greater_larger_positive) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(test_is_greater_positive_vs_negative) {
  s21_decimal val1 = {{1, 2, 3, 655360}};
  s21_decimal val2 = {{3, 2, 1, -2146828288}};
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(test_is_greater_negative_comparison) {
  s21_decimal val1 = {{1, 2, 3, -2146828288}};
  s21_decimal val2 = {{3, 2, 1, -2146828288}};
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(0, result);  // было 1, исправлено на 0
}
END_TEST

START_TEST(test_is_greater_different_scales) {
  s21_decimal val1 = {{1, 2, 3, -2146566144}};
  s21_decimal val2 = {{3, 2, 1, -2146959360}};
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(test_is_greater_negative_vs_positive) {
  s21_decimal val1 = {{10, 2, 3, -2146566144}};
  s21_decimal val2 = {{3, 2, 1, 524288}};
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(test_is_greater_identical_values) {
  s21_decimal val1 = {{1, 2, 3, 917504}};
  s21_decimal val2 = {{1, 2, 3, 917504}};
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(0, result);
}
END_TEST

Suite *test_is_greater(void) {
  Suite *s = suite_create("\033[1;34ms21_is_greater\033[0m");
  TCase *tc = tcase_create("is_greater_tc");
  tcase_add_test(tc, test_is_greater_zero_equal);
  tcase_add_test(tc, test_is_greater_smaller_positive);
  tcase_add_test(tc, test_is_greater_equal_values);
  tcase_add_test(tc, test_is_greater_larger_positive);
  tcase_add_test(tc, test_is_greater_positive_vs_negative);
  tcase_add_test(tc, test_is_greater_negative_comparison);
  tcase_add_test(tc, test_is_greater_different_scales);
  tcase_add_test(tc, test_is_greater_negative_vs_positive);
  tcase_add_test(tc, test_is_greater_identical_values);
  suite_add_tcase(s, tc);
  return s;
}
