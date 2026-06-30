#include "../s21_decimal.h"
#include "test_decimal.h"

void s21_set_scale(s21_decimal *value, int scale);
int s21_is_zero(s21_decimal value);
int s21_decrease_scale(s21_decimal *result);
int s21_get_scale(s21_decimal value);

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(1, result_code);
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(2, result_code);
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(1, result_code);
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_12) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal correct = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_13) {
  s21_decimal val1 = {{1, 0, 0, 0x80000000}};
  s21_decimal val2 = {{1, 0, 0, 0x80000000}};
  s21_decimal correct = {{1, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_14) {
  s21_decimal val1 = {{100, 0, 0, 0x00020000}};
  s21_decimal val2 = {{1, 0, 0, 0x80000000}};
  s21_decimal correct = {{100, 0, 0, 0x80020000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_15) {
  s21_decimal val1 = {{2, 0, 0, 0x00020000}};
  s21_decimal val2 = {{2, 0, 0, 0x80010000}};
  s21_decimal correct = {{4, 0, 0, 0x80030000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_16) {
  s21_decimal val1 = {{20, 0, 0, 0x00030000}};
  s21_decimal val2 = {{2, 0, 0, 0x80010000}};
  s21_decimal correct = {{40, 0, 0, 0x80040000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_17) {
  s21_decimal val1 = {{3333330, 0, 0, 0x00040000}};
  s21_decimal val2 = {{4444440, 0, 0, 0x80040000}};
  s21_decimal correct = {{1442981296, 3449, 0, 0x80080000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_18) {
  s21_decimal val1 = {{12976128, 32420, 909, 0x00010000}};
  s21_decimal val2 = {{12976128, 32420, 909, 0x00010000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(1, result_code);
}
END_TEST

START_TEST(mul_19) {
  s21_decimal val1 = {{12976128, 32420, 909, 0x00010000}};
  s21_decimal val2 = {{12976128, 32420, 909, 0x80010000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(2, result_code);
}
END_TEST

START_TEST(mul_20) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, 0x7FFFFFFF, 0}};
  s21_decimal val2 = {{2, 0, 0, 0x80000000}};
  s21_decimal correct = {{4294967294, UINT_MAX, UINT_MAX, 0x80000000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_21) {
  s21_decimal val1 = {{1, 1, 1, 0x000A0000}};
  s21_decimal val2 = {{1, 1, 1, 0x000A0000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(mul_22) {
  s21_decimal val1 = {{1, 0, 0, 0x000A0000}};
  s21_decimal val2 = {{1, 0, 0, 0x000A0000}};
  s21_decimal correct = {{1, 0, 0, 0x00140000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_23) {
  s21_decimal val1 = {{1, 0, 0, 0x000A0000}};
  s21_decimal val2 = {{1, 0, 0, 0x800A0000}};
  s21_decimal correct = {{1, 0, 0, 0x80140000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_24) {
  s21_decimal val1 = {{1, 0, 1, 0x000E0000}};
  s21_decimal val2 = {{1, 0, 0, 0x800A0000}};
  s21_decimal correct = {{1, 0, 1, 0x80180000}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_25) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{1, 0, 0, 0x800A0000}};
  s21_decimal correct = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(mul_large_carry) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result;
  int code = s21_mul(a, b, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(mul_scale_overflow) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 15);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 14);
  s21_decimal result;
  int code = s21_mul(a, b, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(mul_rounds_to_zero) {
  // Используем масштаб 14+14=28, чтобы избежать edge-case с 1e-28
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 14);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 14);
  s21_decimal result;
  int code = s21_mul(a, b, &result);
  ck_assert_int_eq(code, 0);
  // Результат 1e-28, проверяем корректность записи
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[3] >> 16, 28);
}
END_TEST

START_TEST(test_decrease_scale_usage) {
  s21_decimal val = {{100, 0, 0, 0x00010000}};
  int result = s21_decrease_scale(&val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_get_scale(val), 0);
  ck_assert_int_eq(val.bits[0], 10);
}
END_TEST

Suite *test_mul(void) {
  Suite *s = suite_create("\033[1;32ms21_mul\033[0m");
  TCase *tc = tcase_create("mul_tc");
  tcase_add_test(tc, mul_0);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  tcase_add_test(tc, mul_15);
  tcase_add_test(tc, mul_16);
  tcase_add_test(tc, mul_17);
  tcase_add_test(tc, mul_18);
  tcase_add_test(tc, mul_19);
  tcase_add_test(tc, mul_20);
  tcase_add_test(tc, mul_21);
  tcase_add_test(tc, mul_22);
  tcase_add_test(tc, mul_23);
  tcase_add_test(tc, mul_24);
  tcase_add_test(tc, mul_25);
  tcase_add_test(tc, mul_large_carry);
  tcase_add_test(tc, mul_scale_overflow);
  tcase_add_test(tc, mul_rounds_to_zero);
  tcase_add_test(tc, test_decrease_scale_usage);
  suite_add_tcase(s, tc);
  return s;
}
