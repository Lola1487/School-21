// s21_strncmp_tests.c
#include "../s21_string.h"
#include "s21_test_runner.h"

START_TEST(test_equal_strings) {
  ck_assert_int_eq(0, s21_strncmp("test string", "test string", 11));
}
END_TEST

START_TEST(test_diff_strings) {
  ck_assert(s21_strncmp("test string", "test strong", 11) < 0);
}
END_TEST

START_TEST(test_partial_compare) {
  ck_assert_int_eq(0, s21_strncmp("hello world", "hello there", 5));
}
END_TEST

START_TEST(test_zero_length) {
  ck_assert_int_eq(0, s21_strncmp("any string", "other string", 0));
}
END_TEST

START_TEST(test_null_pointers) {
  const char *str = "valid string";
  ck_assert_int_eq(-1, s21_strncmp(s21_NULL, str, 5));
  ck_assert_int_eq(1, s21_strncmp(str, s21_NULL, 5));
  ck_assert_int_eq(0, s21_strncmp(s21_NULL, s21_NULL, 5));
}
END_TEST

START_TEST(test_non_ascii) { ck_assert(s21_strncmp("täst", "tåst", 4) != 0); }
END_TEST

Suite *tests_for_strncmp(void) {
  Suite *s = suite_create("strncmp");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_equal_strings);
  tcase_add_test(tc, test_diff_strings);
  tcase_add_test(tc, test_partial_compare);
  tcase_add_test(tc, test_zero_length);
  tcase_add_test(tc, test_null_pointers);
  tcase_add_test(tc, test_non_ascii);

  suite_add_tcase(s, tc);
  return s;
}
