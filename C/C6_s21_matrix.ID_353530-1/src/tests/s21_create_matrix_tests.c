#include "s21_test_runner.h"

/* ===== TESTS ===== */

START_TEST(test_create_matrix_normal) {
  s21_matrix A;
  int code = s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_ptr_nonnull(A.matrix);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_1x1) {
  s21_matrix A;
  int code = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(A.rows, 1);
  ck_assert_int_eq(A.columns, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_null_pointer) {
  int code = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_create_matrix_invalid_rows) {
  s21_matrix A;
  int code = s21_create_matrix(0, 3, &A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  code = s21_create_matrix(-1, 3, &A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_create_matrix_invalid_columns) {
  s21_matrix A;
  int code = s21_create_matrix(3, 0, &A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  code = s21_create_matrix(3, -1, &A);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

/* Новый тест для проверки error path в init_matrix */
START_TEST(test_init_matrix_invalid_size) {
  s21_matrix A = {NULL, 0, 0};  // ✅ Инициализация структуры нулями
  // Передаём невалидные размеры, чтобы s21_create_matrix вернул ошибку
  init_matrix(&A, -1, 3, NULL);  // Должно вызвать return в if (!OK)
  // Проверяем, что матрица не создалась
  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

/* ===== SUITE ===== */
// Функция suite должна быть ПОСЛЕ всех тестов, иначе компилятор не видит их
// имена
Suite *create_matrix_suite(void) {
  Suite *s = suite_create("create_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_create_matrix_normal);
  tcase_add_test(tc, test_create_matrix_1x1);
  tcase_add_test(tc, test_create_matrix_null_pointer);
  tcase_add_test(tc, test_create_matrix_invalid_rows);
  tcase_add_test(tc, test_create_matrix_invalid_columns);
  tcase_add_test(tc, test_init_matrix_invalid_size);  // ✅ Добавлен новый тест

  suite_add_tcase(s, tc);
  return s;
}
