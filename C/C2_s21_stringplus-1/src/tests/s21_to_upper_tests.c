#include <stdlib.h>
#include <string.h>

#include "s21_test_runner.h"

#define LONG_STR 1000

// Мок malloc для эмуляции ошибки выделения памяти
static void *mock_malloc_fail(size_t size) {
  (void)size;
  return NULL;
}

// Внешний malloc_ptr из s21_to_upper.c
extern void *(*malloc_ptr)(size_t);

START_TEST(test_s21_to_upper_0) {
  const char *str = s21_NULL;
  char *result = s21_to_upper(str);
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_s21_to_upper_1) {
  const char *str = "";
  const char *expected = "";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_2) {
  const char *str = " ";
  const char *expected = " ";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_3) {
  const char *str = "hello world";
  const char *expected = "HELLO WORLD";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_4) {
  const char *str = "aBcDeFgHiJkLmNoPqRsTuVwXyZ";
  const char *expected = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_5) {
  const char *str = "12345!@#$%";
  const char *expected = "12345!@#$%";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_6) {
  const char *str = "lowercase WITH UPPERCASE";
  const char *expected = "LOWERCASE WITH UPPERCASE";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_7) {
  const char *str = "!@#$%^&*()_+{}|:\"<>?`~[]\\;',./";
  const char *expected = "!@#$%^&*()_+{}|:\"<>?`~[]\\;',./";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_8) {
  const char *str = "ALREADY UPPERCASE";
  const char *expected = "ALREADY UPPERCASE";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_9) {
  char str[LONG_STR + 1];
  char expected[LONG_STR + 1];
  for (size_t i = 0; i < LONG_STR; i++) {
    str[i] = 'a' + (i % 26);
    expected[i] = 'A' + (i % 26);
  }
  str[LONG_STR] = '\0';
  expected[LONG_STR] = '\0';

  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест с имитацией провала malloc (возврат NULL)
START_TEST(test_s21_to_upper_malloc_fail) {
  void *(*old_malloc)(size_t) = malloc_ptr;
  malloc_ptr = mock_malloc_fail;

  const char *str = "test";
  char *result = s21_to_upper(str);
  ck_assert_ptr_eq(result, s21_NULL);

  malloc_ptr = old_malloc;
}
END_TEST

// Формирование сьюта для запуска тестов
Suite *tests_for_to_upper(void) {
  Suite *s = suite_create("to_upper_tests");
  TCase *tc_to_upper = tcase_create("to_upper_tc");

  tcase_add_test(tc_to_upper, test_s21_to_upper_0);
  tcase_add_test(tc_to_upper, test_s21_to_upper_1);
  tcase_add_test(tc_to_upper, test_s21_to_upper_2);
  tcase_add_test(tc_to_upper, test_s21_to_upper_3);
  tcase_add_test(tc_to_upper, test_s21_to_upper_4);
  tcase_add_test(tc_to_upper, test_s21_to_upper_5);
  tcase_add_test(tc_to_upper, test_s21_to_upper_6);
  tcase_add_test(tc_to_upper, test_s21_to_upper_7);
  tcase_add_test(tc_to_upper, test_s21_to_upper_8);
  tcase_add_test(tc_to_upper, test_s21_to_upper_9);
  tcase_add_test(tc_to_upper, test_s21_to_upper_malloc_fail);

  suite_add_tcase(s, tc_to_upper);
  return s;
}
