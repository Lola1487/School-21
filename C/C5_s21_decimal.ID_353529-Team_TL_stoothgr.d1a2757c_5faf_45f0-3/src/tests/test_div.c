#include "../s21_decimal.h"
#include "test_decimal.h"

void s21_set_scale(s21_decimal *val, int scale);
int s21_is_zero(s21_decimal val);

START_TEST(div_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(3, result_code);
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(3, result_code);
}
END_TEST

START_TEST(div_5) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char res1[1000], res2[1000] = "3100000000 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", (unsigned int)z.bits[0],
           (unsigned int)z.bits[1], (unsigned int)z.bits[2],
           (unsigned int)z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(div_6) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{3100000000, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char res1[1000], res2[1000] = "1854727993 751066592 0 1835008";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", (unsigned int)z.bits[0],
           (unsigned int)z.bits[1], (unsigned int)z.bits[2],
           (unsigned int)z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(div_7) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", (unsigned int)z.bits[0],
           (unsigned int)z.bits[1], (unsigned int)z.bits[2],
           (unsigned int)z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_8) {
  s21_decimal val1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000010, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(1, result_code);
}
END_TEST

START_TEST(div_9) {
  s21_decimal val1 = {
      {0b00000000000000000000000000001011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000010, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal correct = {
      {0b00000000000000000000000000110111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000010000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_10) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal correct = {
      {0b00000000000000000000000001001011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000100000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_11) {
  s21_decimal val1 = {
      {0b00000000000000000000000000100001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000010000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000101100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000010000000000000000}};
  s21_decimal correct = {
      {0b00000000000000000000000001001011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000100000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_12) {
  s21_decimal val1 = {
      {0b00000000000000000000000101001010, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000100000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000110111000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000100000000000000000}};
  s21_decimal correct = {
      {0b00000000000000000000000001001011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000100000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_13) {
  s21_decimal val1 = {
      {0b00000000001100101101110011010101, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b00000000010000111101000100011100, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal correct = {
      {0b00000000000000000000000001001011, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000100000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_14) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal val2 = {
      {0b10010000111011011101000000000000, 0b00000000000000000000000000101110,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal correct = {
      {0b00000000000000000000000000000101, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000011000000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_15) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b00000000000010100000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b00000000000010100000000000000000}};
  s21_decimal correct = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_16) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b00000000000010100000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b00000000000011110000000000000000}};
  s21_decimal correct = {
      {0b00000000000000011000011010100000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_17) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b00000000000010100000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000001010,
       0b00000000000000000000000000000001, 0b10000000000011110000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(1, result_code);
}
END_TEST

START_TEST(div_18) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b00000000000011110000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b10000000000011110000000000000000}};
  s21_decimal correct = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(div_19) {
  s21_decimal val1 = {
      {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000011110000000000000000}};
  s21_decimal val2 = {
      {0b00000000000000000000000000000001, 0b00000000000000000000000000000001,
       0b00000000000000000000000000000001, 0b10000000000011110000000000000000}};
  s21_decimal correct = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

/* ===== НОВЫЕ ТЕСТЫ ДЛЯ 100% ПОКРЫТИЯ ===== */
START_TEST(div_scale2_greater) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0x00010000}};
  s21_decimal result;
  int code = s21_div(a, b, &result);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(div_rounding_needed) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result;
  int code = s21_div(a, b, &result);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(div_rounding_half_up) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{8, 0, 0, 0}};
  s21_decimal result;
  int code = s21_div(a, b, &result);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(div_repeating_decimal) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;
  int code = s21_div(a, b, &result);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(div_rounds_to_zero) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 28);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result;
  int code = s21_div(a, b, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_zero(result), 1);
}
END_TEST

Suite *test_div(void) {
  Suite *s = suite_create("\033[1;32ms21_div\033[0m");
  TCase *tc = tcase_create("div_tc");
  tcase_add_test(tc, div_0);
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_9);
  tcase_add_test(tc, div_10);
  tcase_add_test(tc, div_11);
  tcase_add_test(tc, div_12);
  tcase_add_test(tc, div_13);
  tcase_add_test(tc, div_14);
  tcase_add_test(tc, div_15);
  tcase_add_test(tc, div_16);
  tcase_add_test(tc, div_17);
  tcase_add_test(tc, div_18);
  tcase_add_test(tc, div_19);
  tcase_add_test(tc, div_scale2_greater);
  tcase_add_test(tc, div_rounding_needed);
  tcase_add_test(tc, div_rounding_half_up);
  tcase_add_test(tc, div_repeating_decimal);
  tcase_add_test(tc, div_rounds_to_zero);
  suite_add_tcase(s, tc);
  return s;
}
