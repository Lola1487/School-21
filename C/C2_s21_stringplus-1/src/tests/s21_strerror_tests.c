#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_test_runner.h"

START_TEST(s21_strerror_known_errors) {
  // Проверяем известные коды ошибок (0-133)
  for (int i = 0; i <= 133; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(s21_strerror_negative) {
  int i = -54;
  char expected[256];
  snprintf(expected, sizeof(expected), "Unknown error: %d", i);
  ck_assert_str_eq(expected, s21_strerror(i));
}
END_TEST

START_TEST(s21_strerror_above_range) {
  int i = 134;
  char expected[256];
  snprintf(expected, sizeof(expected), "Unknown error: %d", i);
  ck_assert_str_eq(expected, s21_strerror(i));
}
END_TEST

START_TEST(s21_strerror_large_number) {
  int i = 9999;
  char expected[256];
  snprintf(expected, sizeof(expected), "Unknown error: %d", i);
  ck_assert_str_eq(expected, s21_strerror(i));
}
END_TEST

Suite *tests_for_strerror(void) {
  Suite *s;
  TCase *tc_strerror;

  s = suite_create("strerror_tests");
  tc_strerror = tcase_create("strerror_tc");

  tcase_add_test(tc_strerror, s21_strerror_known_errors);
  tcase_add_test(tc_strerror, s21_strerror_negative);
  tcase_add_test(tc_strerror, s21_strerror_above_range);
  tcase_add_test(tc_strerror, s21_strerror_large_number);

  suite_add_tcase(s, tc_strerror);

  return s;
}
