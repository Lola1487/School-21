#include "../s21_decimal.h"  // Исправлен путь к заголовку
#include "test_decimal.h"

/* Test 1: Positive numbers without fractional part should remain unchanged */
START_TEST(test_round_positive_no_fraction) {
  s21_decimal value = {{1, 2, 3, 917504}};
  s21_decimal expected = {{553402, 0, 0, 0}};
  s21_decimal value2 = {{16, 100, 3, 851968}};
  s21_decimal expected2 = {{5534023, 0, 0, 0}};
  s21_decimal value3 = {{2112827408, 798, 3, 851968}};
  s21_decimal expected3 = {{5534024, 0, 0, 0}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  s21_decimal result2;
  int error_code2 = s21_round(value2, &result2);
  s21_decimal result3;
  int error_code3 = s21_round(value3, &result3);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
  ck_assert_int_eq(error_code3, 0);
  ck_assert_mem_eq(&result3, &expected3, sizeof(s21_decimal));
}
END_TEST

/* Test 2: Negative numbers without fractional part should remain unchanged */
START_TEST(test_round_negative_no_fraction) {
  s21_decimal value = {{-1662697471, 4658, 3, -2146566144}};
  s21_decimal expected = {{553403, 0, 0, -2147483648}};
  s21_decimal value2 = {{16, 100, 3, -2146631680}};
  s21_decimal expected2 = {{5534023, 0, 0, -2147483648}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  s21_decimal result2;
  int error_code2 = s21_round(value2, &result2);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

/* Test 3: Positive numbers with fractional part >= 0.5 should round up */
START_TEST(test_round_positive_fraction_half) {
  s21_decimal value = {{25, 30, 0, 65536}};
  s21_decimal expected = {{3, 3, 0, 0}};
  s21_decimal value2 = {{3, 3, 0, 0}};
  s21_decimal expected2 = {{3, 3, 0, 0}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  s21_decimal result2;
  int error_code2 = s21_round(value2, &result2);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

/* Test 4: Positive numbers with fractional part < 0.5 should round down */
START_TEST(test_round_positive_fraction_less_half) {
  s21_decimal value = {{225, 300, 0, 131072}};
  s21_decimal expected = {{2, 3, 0, 0}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 5: Negative numbers with fractional part >= 0.5 should round down */
START_TEST(test_round_negative_fraction_half) {
  s21_decimal value = {{792095801, -1320247423, 6, -2147418112}};
  s21_decimal expected = {{-350287149, -1420514932, 0, -2147483648}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 6: Numbers with small fractional parts should round to zero */
START_TEST(test_round_zero) {
  s21_decimal value = {{25, 0, 0, 131072}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal value2 = {{10, 100, 3, 1376256}};
  s21_decimal expected2 = {{0, 0, 0, 0}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  s21_decimal result2;
  int error_code2 = s21_round(value2, &result2);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
  ck_assert_int_eq(error_code2, 0);
  ck_assert_mem_eq(&result2, &expected2, sizeof(s21_decimal));
}
END_TEST

/* Test 7: Positive numbers with very small fractional parts */
START_TEST(test_round_small_fraction_positive) {
  s21_decimal value = {{10625, 10000, 0, 262144}};
  s21_decimal expected = {{1, 1, 0, 0}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 8: Negative numbers with very small fractional parts */
START_TEST(test_round_small_fraction_negative) {
  s21_decimal value = {{10625, 100000, 0, -2147221504}};
  s21_decimal expected = {{1, 10, 0, -2147483648}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 9: Positive numbers with exact 0.5 fractional part */
START_TEST(test_round_positive_exact_half) {
  s21_decimal value = {{15, 10, 0, 65536}};
  s21_decimal expected = {{2, 1, 0, 0}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/* Test 10: Negative numbers with exact 0.5 fractional part */
START_TEST(test_round_negative_exact_half) {
  s21_decimal value = {{15, 10, 0, -2147418112}};
  s21_decimal expected = {{2, 1, 0, -2147483648}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// ===== НОВЫЙ ТЕСТ: Обработка NaN (покрывает строку с return 1) =====
START_TEST(test_round_nan) {
  s21_decimal nan_val = {{0, 0, 0, 0x001D0000}};  // scale = 29 → NaN
  s21_decimal result;
  int code = s21_round(nan_val, &result);
  ck_assert_int_eq(code, 1);  // Должен вернуть ошибку
}
END_TEST

// ===== НОВЫЙ ТЕСТ: Обработка нуля (покрывает строки 15-17) =====
START_TEST(test_round_zero_value) {
  s21_decimal value = {{0, 0, 0, 0}};  // Zero value
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result;
  int error_code = s21_round(value, &result);
  ck_assert_int_eq(error_code, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

Suite *test_round(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[1;33ms21_round\033[0m");
  tc_core = tcase_create("round_tc");
  tcase_add_test(tc_core, test_round_positive_no_fraction);
  tcase_add_test(tc_core, test_round_negative_no_fraction);
  tcase_add_test(tc_core, test_round_positive_fraction_half);
  tcase_add_test(tc_core, test_round_positive_fraction_less_half);
  tcase_add_test(tc_core, test_round_negative_fraction_half);
  tcase_add_test(tc_core, test_round_zero);
  tcase_add_test(tc_core, test_round_small_fraction_positive);
  tcase_add_test(tc_core, test_round_small_fraction_negative);
  tcase_add_test(tc_core, test_round_positive_exact_half);
  tcase_add_test(tc_core, test_round_negative_exact_half);
  tcase_add_test(tc_core, test_round_nan);
  tcase_add_test(tc_core, test_round_zero_value);  // Добавлен новый тест
  suite_add_tcase(s, tc_core);
  return s;
}
