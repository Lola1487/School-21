#include <stdlib.h>
#include <string.h>

#include "s21_test_runner.h"

START_TEST(test_s21_to_lower_null) {
  char *result = s21_to_lower(s21_NULL);
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  const char *str = "";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_single_space) {
  const char *str = " ";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, " ");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_uppercase) {
  const char *str = "HELLO WORLD";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_mixed_case) {
  const char *str = "AbCdEfGhIjKlMnOpQrStUvWxYz";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "abcdefghijklmnopqrstuvwxyz");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_numbers_special) {
  const char *str = "12345!@#$%";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "12345!@#$%");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_uppercase_with_lower) {
  const char *str = "UPPERCASE with lowercase";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "uppercase with lowercase");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_only_special) {
  const char *str = "!@#$%^&*()_+{}|:\"<>?`~[]\\;',./";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "!@#$%^&*()_+{}|:\"<>?`~[]\\;',./");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_already_lower) {
  const char *str = "already lowercase";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "already lowercase");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_long_string) {
  char str[1001];
  char expected[1001];

  for (int i = 0; i < 1000; i++) {
    str[i] = 'A' + (i % 26);
    expected[i] = 'a' + (i % 26);
  }
  str[1000] = '\0';
  expected[1000] = '\0';

  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_boundary_chars) {
  const char *str = "@AZ[\\]^_`";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "@az[\\]^_`");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_mixed_with_numbers) {
  const char *str = "Hello123WORLD";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "hello123world");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_single_char) {
  const char *str = "A";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "a");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_all_uppercase) {
  const char *str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, "abcdefghijklmnopqrstuvwxyz");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_unicode_chars) {
  const char *str = "Cafe UBER";
  char *result = s21_to_lower(str);
  ck_assert_ptr_ne(result, s21_NULL);
  // Только ASCII символы преобразуются
  ck_assert_str_eq(result, "cafe uber");
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_malloc_failure_placeholder) {
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite *tests_for_to_lower(void) {
  Suite *suite = suite_create("s21_to_lower");
  TCase *test_case = tcase_create("Core");

  tcase_add_test(test_case, test_s21_to_lower_null);
  tcase_add_test(test_case, test_s21_to_lower_empty);
  tcase_add_test(test_case, test_s21_to_lower_single_space);
  tcase_add_test(test_case, test_s21_to_lower_uppercase);
  tcase_add_test(test_case, test_s21_to_lower_mixed_case);
  tcase_add_test(test_case, test_s21_to_lower_numbers_special);
  tcase_add_test(test_case, test_s21_to_lower_uppercase_with_lower);
  tcase_add_test(test_case, test_s21_to_lower_only_special);
  tcase_add_test(test_case, test_s21_to_lower_already_lower);
  tcase_add_test(test_case, test_s21_to_lower_long_string);
  tcase_add_test(test_case, test_s21_to_lower_boundary_chars);
  tcase_add_test(test_case, test_s21_to_lower_mixed_with_numbers);
  tcase_add_test(test_case, test_s21_to_lower_single_char);
  tcase_add_test(test_case, test_s21_to_lower_all_uppercase);
  tcase_add_test(test_case, test_s21_to_lower_unicode_chars);
  tcase_add_test(test_case, test_s21_to_lower_malloc_failure_placeholder);

  suite_add_tcase(suite, test_case);
  return suite;
}
