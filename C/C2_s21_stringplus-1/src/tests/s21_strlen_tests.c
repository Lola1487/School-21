#include "../s21_string.h"
#include "s21_test_runner.h"

START_TEST(s21_strlen_empty_string) {
  const char* str = "";
  ck_assert_int_eq(0, s21_strlen(str));
}
END_TEST

START_TEST(s21_strlen_long_string) {
  static char str[1000001];
  for (int i = 0; i < 1000000; i++) {
    str[i] = 'a';
  }
  str[1000000] = '\0';

  ck_assert_int_eq(1000000, s21_strlen(str));
}
END_TEST

START_TEST(s21_strlen_null_pointer) {
  ck_assert_int_eq(0, s21_strlen(s21_NULL));
}
END_TEST

Suite* tests_for_strlen(void) {
  Suite* s;
  TCase* tc_strlen;

  s = suite_create("strlen_tests");
  tc_strlen = tcase_create("strlen_tc");

  tcase_add_test(tc_strlen, s21_strlen_empty_string);
  tcase_add_test(tc_strlen, s21_strlen_long_string);
  tcase_add_test(tc_strlen, s21_strlen_null_pointer);

  suite_add_tcase(s, tc_strlen);

  return s;
}
