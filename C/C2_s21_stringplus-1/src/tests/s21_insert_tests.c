// test_s21_insert.c
#include "../s21_string.h"
#include "s21_test_runner.h"

START_TEST(test_s21_insert_empty_src_and_dest) {
  // ARRANGE
  const char* src_str = "";
  const char* str = "abc";
  const char* expected = "abc";

  // ACT
  char* result = s21_insert(src_str, str, 0);

  // ASSERT
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_empty_src_nonempty_dest) {
  // ARRANGE
  const char* src_str = "";
  const char* str = "abc";
  const char* expected = "abc";

  // ACT
  char* result = s21_insert(src_str, str, 0);

  // ASSERT
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

/**
 * @brief Тестирует функцию s21_insert() с непустыми исходной и вставляемой
 * строками.
 *
 * @details Вставляет строку "abc" в середину строки "defgh".
 */
START_TEST(test_s21_insert_nonempty_src_and_dest) {
  // ARRANGE
  const char* src_str = "defgh";
  const char* str = "abc";
  const char* expected = "deabcfgh";

  // ACT
  char* result = s21_insert(src_str, str, 2);

  // ASSERT
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_start_of_string) {
  // ARRANGE
  const char* src_str = "defgh";
  const char* str = "abc";
  const char* expected = "abcdefgh";

  // ACT
  char* result = s21_insert(src_str, str, 0);

  // ASSERT
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_end_of_string) {
  // ARRANGE
  const char* src_str = "defgh";
  const char* str = "abc";
  const char* expected = "defghabc";

  // ACT
  char* result = s21_insert(src_str, str, s21_strlen(src_str));

  // ASSERT
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_memory_allocation) {
  // ARRANGE
  const char* src_str = "";
  const char* str = "abc";
  const char* expected = "abc";

  // ACT
  char* result = s21_insert(src_str, str, 0);

  // ASSERT
  ck_assert_ptr_ne(result, s21_NULL);  // Проверяем, что память выделена
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест для NULL source (покрывает строку 8)
START_TEST(test_s21_insert_null_src) {
  // ACT
  char* result = s21_insert(NULL, "test", 0);

  // ASSERT
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

// Тест для NULL str (покрывает строку 8)
START_TEST(test_s21_insert_null_str) {
  // ACT
  char* result = s21_insert("source", NULL, 0);

  // ASSERT
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

// Тест для обоих NULL (покрывает строку 8)
START_TEST(test_s21_insert_both_null) {
  // ACT
  char* result = s21_insert(NULL, NULL, 0);

  // ASSERT
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

// Тест для index > длины строки (покрывает строку 21)
START_TEST(test_s21_insert_index_out_of_bounds) {
  // ARRANGE
  const char* src_str = "abc";

  // ACT
  char* result = s21_insert(src_str, "test", 5);

  // ASSERT
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

// Тест для index = длине строки (должен работать)
START_TEST(test_s21_insert_index_at_end) {
  // ARRANGE
  const char* src_str = "abc";
  const char* expected = "abctest";

  // ACT
  char* result = s21_insert(src_str, "test", 3);

  // ASSERT
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест для index = 0 с пустой src
START_TEST(test_s21_insert_zero_index_empty_src) {
  // ARRANGE
  const char* src_str = "";
  const char* expected = "test";

  // ACT
  char* result = s21_insert(src_str, "test", 0);

  // ASSERT
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест для вставки в середину длинной строки
START_TEST(test_s21_insert_middle_of_long_string) {
  // ARRANGE
  const char* src_str = "hello world";
  const char* str = " beautiful";
  const char* expected = "hello beautiful world";

  // ACT
  char* result = s21_insert(src_str, str, 5);

  // ASSERT
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

// Тест для вставки пустой строки в непустую
START_TEST(test_s21_insert_empty_string) {
  // ARRANGE
  const char* src_str = "hello";
  const char* str = "";
  const char* expected = "hello";

  // ACT
  char* result = s21_insert(src_str, str, 2);

  // ASSERT
  ck_assert_ptr_ne(result, s21_NULL);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

Suite* tests_for_insert(void) {
  Suite* s;
  TCase* tc_insert;
  s = suite_create("Insert Tests");
  tc_insert = tcase_create("Insert Test Case");

  // Существующие тесты
  tcase_add_test(tc_insert, test_s21_insert_empty_src_and_dest);
  tcase_add_test(tc_insert, test_s21_insert_empty_src_nonempty_dest);
  tcase_add_test(tc_insert, test_s21_insert_nonempty_src_and_dest);
  tcase_add_test(tc_insert, test_s21_insert_start_of_string);
  tcase_add_test(tc_insert, test_s21_insert_end_of_string);
  tcase_add_test(tc_insert, test_s21_insert_memory_allocation);

  // Новые тесты для покрытия строк 8 и 21
  tcase_add_test(tc_insert, test_s21_insert_null_src);
  tcase_add_test(tc_insert, test_s21_insert_null_str);
  tcase_add_test(tc_insert, test_s21_insert_both_null);
  tcase_add_test(tc_insert, test_s21_insert_index_out_of_bounds);
  tcase_add_test(tc_insert, test_s21_insert_index_at_end);
  tcase_add_test(tc_insert, test_s21_insert_zero_index_empty_src);
  tcase_add_test(tc_insert, test_s21_insert_middle_of_long_string);
  tcase_add_test(tc_insert, test_s21_insert_empty_string);

  suite_add_tcase(s, tc_insert);

  return s;
}
