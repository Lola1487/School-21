#include "s21_test_runner.h"

START_TEST(test_strstr_found_at_start) {
  const char *str = "hello world";
  const char *pattern = "hell";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_found_in_middle) {
  const char *str = "hello world";
  const char *pattern = "world";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_found_at_end) {
  const char *str = "hello world";
  const char *pattern = "ld";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_not_found) {
  const char *str = "hello world";
  const char *pattern = "universe";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_empty_substring) {
  const char *str = "hello world";
  const char *pattern = "";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_empty_input_string) {
  const char *str = "";
  const char *pattern = "anything";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_full_match) {
  const char *str = "hello";
  const char *pattern = "hello";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_multiple_occurrences) {
  const char *str = "abcabcabc";
  const char *pattern = "abc";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_long_string_with_match) {
  char str[1000];
  for (int i = 0; i < 999; ++i) {
    str[i] = (i == 500) ? 'x' : 'a';
  }
  str[999] = '\0';
  const char *pattern = "x";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_substring_longer_than_string) {
  const char *str = "short";
  const char *pattern = "longsubstring";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_repeated_characters) {
  const char *str = "aaaaaaaaaa";
  const char *pattern = "aaa";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_whitespace_only) {
  const char *str = "    ";
  const char *pattern = " ";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_with_escape_sequences) {
  const char *str = "Line1\nLine2\tTab";
  const char *pattern = "\nLine2";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_strstr_similar_substrings) {
  const char *str = "abcdefabcxy";
  const char *pattern = "abcxy";

  char *result = s21_strstr(str, pattern);
  char *expected = strstr(str, pattern);

  ck_assert_ptr_eq(result, expected);
}
END_TEST

// NEW TESTS FOR NULL PARAMETERS (COVERS LINE 8)

START_TEST(test_strstr_null_haystack) {
  const char *pattern = "test";

  char *result = s21_strstr(s21_NULL, pattern);

  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_strstr_null_needle) {
  const char *haystack = "test string";

  char *result = s21_strstr(haystack, s21_NULL);

  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_strstr_both_null) {
  char *result = s21_strstr(s21_NULL, s21_NULL);

  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

START_TEST(test_strstr_empty_needle_with_null_haystack) {
  const char *pattern = "";

  char *result = s21_strstr(s21_NULL, pattern);

  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

Suite *tests_for_strstr(void) {
  Suite *s = suite_create("s21_strstr_tests");
  TCase *tc_core = tcase_create("CoreFunctionality");

  // Original tests
  tcase_add_test(tc_core, test_strstr_found_at_start);
  tcase_add_test(tc_core, test_strstr_found_in_middle);
  tcase_add_test(tc_core, test_strstr_found_at_end);
  tcase_add_test(tc_core, test_strstr_not_found);
  tcase_add_test(tc_core, test_strstr_empty_substring);
  tcase_add_test(tc_core, test_strstr_empty_input_string);
  tcase_add_test(tc_core, test_strstr_full_match);
  tcase_add_test(tc_core, test_strstr_multiple_occurrences);
  tcase_add_test(tc_core, test_strstr_long_string_with_match);
  tcase_add_test(tc_core, test_strstr_substring_longer_than_string);
  tcase_add_test(tc_core, test_strstr_repeated_characters);
  tcase_add_test(tc_core, test_strstr_whitespace_only);
  tcase_add_test(tc_core, test_strstr_with_escape_sequences);
  tcase_add_test(tc_core, test_strstr_similar_substrings);

  // New tests for NULL parameters
  tcase_add_test(tc_core, test_strstr_null_haystack);
  tcase_add_test(tc_core, test_strstr_null_needle);
  tcase_add_test(tc_core, test_strstr_both_null);
  tcase_add_test(tc_core, test_strstr_empty_needle_with_null_haystack);

  suite_add_tcase(s, tc_core);

  return s;
}
