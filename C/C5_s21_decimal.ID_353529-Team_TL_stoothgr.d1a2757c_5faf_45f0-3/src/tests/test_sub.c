#include "test_decimal.h"

START_TEST(test_sub_negative_minus_positive_small) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_positive_minus_negative_small) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_negative_minus_negative_small) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_positive_minus_positive_equal) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_positive_minus_positive_normal) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_positive_minus_positive_negative_result) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_negative_minus_positive_negative_result) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_negative_minus_positive_smaller_result) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_positive_minus_negative_positive_result) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_positive_minus_negative_larger_result) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_negative_minus_zero) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_max_negative_minus_positive_overflow) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(2, result_code);
}
END_TEST

START_TEST(test_sub_max_positive_minus_positive_no_overflow) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_max_negative_minus_negative_no_overflow) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_small_negative_minus_max_positive_overflow) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(2, result_code);
}
END_TEST

START_TEST(test_sub_small_positive_minus_max_positive_no_overflow) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_small_negative_minus_max_negative_no_overflow) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_max_positive_minus_negative_overflow) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(1, result_code);
}
END_TEST

START_TEST(test_sub_small_positive_minus_max_negative_overflow) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(1, result_code);
}
END_TEST

START_TEST(test_sub_equal_positive_values_zero_result) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(test_sub_large_values_with_exponent_positive_minus_negative) {
  s21_decimal val1 = {{1, 1, 1, 0x00010000}};
  s21_decimal val2 = {{1, 1, 1, 0x80010000}};
  s21_decimal expected = {{2, 2, 2, 0x00010000}};
  s21_decimal res = {{0}};
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(expected.bits[0], res.bits[0]);
  ck_assert_int_eq(expected.bits[1], res.bits[1]);
  ck_assert_int_eq(expected.bits[2], res.bits[2]);
  ck_assert_int_eq(expected.bits[3], res.bits[3]);
}
END_TEST

START_TEST(test_sub_equal_negative_values_with_exponent_zero_result) {
  s21_decimal val1 = {{1, 1, 1, 0x80010000}};
  s21_decimal val2 = {{1, 1, 1, 0x80010000}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(expected.bits[0], res.bits[0]);
  ck_assert_int_eq(expected.bits[1], res.bits[1]);
  ck_assert_int_eq(expected.bits[2], res.bits[2]);
  ck_assert_int_eq(expected.bits[3], res.bits[3]);
}
END_TEST

START_TEST(test_sub_negative_minus_positive_with_exponent) {
  s21_decimal val1 = {{1, 1, 1, 0x80010000}};
  s21_decimal val2 = {{1, 1, 1, 0x00010000}};
  s21_decimal expected = {{2, 2, 2, 0x80010000}};
  s21_decimal res = {{0}};
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(expected.bits[0], res.bits[0]);
  ck_assert_int_eq(expected.bits[1], res.bits[1]);
  ck_assert_int_eq(expected.bits[2], res.bits[2]);
  ck_assert_int_eq(expected.bits[3], res.bits[3]);
}
END_TEST

START_TEST(test_sub_zero_minus_positive_with_exponent) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{1, 1, 1, 0x00010000}};
  s21_decimal expected = {{1, 1, 1, 0x80010000}};
  s21_decimal res = {{0}};
  int result_code = s21_sub(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(expected.bits[0], res.bits[0]);
  ck_assert_int_eq(expected.bits[1], res.bits[1]);
  ck_assert_int_eq(expected.bits[2], res.bits[2]);
  ck_assert_int_eq(expected.bits[3], res.bits[3]);
}
END_TEST

Suite *test_sub(void) {
  Suite *s = suite_create("\033[1;32ms21_sub\033[0m");
  TCase *tc = tcase_create("sub_tc");
  tcase_add_test(tc, test_sub_negative_minus_positive_small);
  tcase_add_test(tc, test_sub_positive_minus_negative_small);
  tcase_add_test(tc, test_sub_negative_minus_negative_small);
  tcase_add_test(tc, test_sub_positive_minus_positive_equal);
  tcase_add_test(tc, test_sub_positive_minus_positive_normal);
  tcase_add_test(tc, test_sub_positive_minus_positive_negative_result);
  tcase_add_test(tc, test_sub_negative_minus_positive_negative_result);
  tcase_add_test(tc, test_sub_negative_minus_positive_smaller_result);
  tcase_add_test(tc, test_sub_positive_minus_negative_positive_result);
  tcase_add_test(tc, test_sub_positive_minus_negative_larger_result);
  tcase_add_test(tc, test_sub_negative_minus_zero);
  tcase_add_test(tc, test_sub_max_negative_minus_positive_overflow);
  tcase_add_test(tc, test_sub_max_positive_minus_positive_no_overflow);
  tcase_add_test(tc, test_sub_max_negative_minus_negative_no_overflow);
  tcase_add_test(tc, test_sub_small_negative_minus_max_positive_overflow);
  tcase_add_test(tc, test_sub_small_positive_minus_max_positive_no_overflow);
  tcase_add_test(tc, test_sub_small_negative_minus_max_negative_no_overflow);
  tcase_add_test(tc, test_sub_max_positive_minus_negative_overflow);
  tcase_add_test(tc, test_sub_small_positive_minus_max_negative_overflow);
  tcase_add_test(tc, test_sub_equal_positive_values_zero_result);
  tcase_add_test(tc,
                 test_sub_large_values_with_exponent_positive_minus_negative);
  tcase_add_test(tc, test_sub_equal_negative_values_with_exponent_zero_result);
  tcase_add_test(tc, test_sub_negative_minus_positive_with_exponent);
  tcase_add_test(tc, test_sub_zero_minus_positive_with_exponent);
  suite_add_tcase(s, tc);
  return s;
}
