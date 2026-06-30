#include "test_decimal.h"

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(1, result_code);
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(2, result_code);
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(2, result_code);
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(2, result_code);
}
END_TEST

START_TEST(add_17) {
  s21_decimal val1 = {{1, 1, 1, 0x00010000}};
  s21_decimal val2 = {{1, 1, 1, 0x00010000}};
  s21_decimal correct = {{2, 2, 2, 0x00010000}};
  s21_decimal res = {{0}};
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {{1, 1, 1, 0x00010000}};
  s21_decimal val2 = {{1, 1, 1, 0x000A0000}};
  s21_decimal res = {{0}};
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_19) {
  s21_decimal val1 = {{24, 1, 1, 0x80010000}};
  s21_decimal val2 = {{1, 15, 1, 0x000A0000}};
  s21_decimal res = {{0}};
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_20) {
  s21_decimal val1 = {{24, 1, 1, 0x80010000}};
  s21_decimal val2 = {{1, 15, 1, 0x000A0000}};
  s21_decimal res = {{0}};
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_21) {
  s21_decimal val1 = {{1, 1, 1, 0x000A0000}};
  s21_decimal val2 = {{1, 1, 1, 0x80010000}};
  s21_decimal res = {{0}};
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
}
END_TEST

START_TEST(add_22) {
  s21_decimal val1 = {{1, 1, 1, 0x80010000}};
  s21_decimal val2 = {{1, 1, 1, 0x00010000}};
  s21_decimal correct = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int result_code = s21_add(val1, val2, &res);
  ck_assert_int_eq(0, result_code);
  ck_assert_int_eq(correct.bits[0], res.bits[0]);
  ck_assert_int_eq(correct.bits[1], res.bits[1]);
  ck_assert_int_eq(correct.bits[2], res.bits[2]);
  ck_assert_int_eq(correct.bits[3], res.bits[3]);
}
END_TEST

Suite *test_add(void) {
  Suite *s = suite_create("\033[1;32ms21_add\033[0m");
  TCase *tc = tcase_create("add_tc");
  tcase_add_test(tc, add_0);
  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);
  tcase_add_test(tc, add_10);
  tcase_add_test(tc, add_11);
  tcase_add_test(tc, add_12);
  tcase_add_test(tc, add_13);
  tcase_add_test(tc, add_14);
  tcase_add_test(tc, add_15);
  tcase_add_test(tc, add_16);
  tcase_add_test(tc, add_17);
  tcase_add_test(tc, add_18);
  tcase_add_test(tc, add_19);
  tcase_add_test(tc, add_20);
  tcase_add_test(tc, add_21);
  tcase_add_test(tc, add_22);
  suite_add_tcase(s, tc);
  return s;
}
