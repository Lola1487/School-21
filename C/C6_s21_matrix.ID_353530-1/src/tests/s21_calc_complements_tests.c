#include "s21_test_runner.h"

START_TEST(test_calc_complements_2x2) {
  // ARRANGE: Create a 2x2 matrix for which to calculate complements
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Calculate matrix of algebraic complements
  int code = s21_calc_complements(&A, &B);

  // ASSERT: Verify the resulting matrix dimensions and values
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(B.rows, 2);
  ck_assert_int_eq(B.columns, 2);
  ck_assert_double_eq_tol(B.matrix[0][0], 4.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[0][1], -3.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][0], -2.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][1], 1.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_calc_complements_3x3) {
  // ARRANGE: Create a 3x3 matrix with known complement values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0, 1.0};
  init_matrix(&A, 3, 3, values);

  // ACT: Calculate matrix of algebraic complements
  int code = s21_calc_complements(&A, &B);

  // ASSERT: Verify dimensions and specific complement values
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(B.rows, 3);
  ck_assert_int_eq(B.columns, 3);
  ck_assert_double_eq_tol(B.matrix[0][0], 0.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[0][1], 10.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[0][2], -20.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_calc_complements_1x1) {
  // ARRANGE: Create a 1x1 matrix
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {5.0};
  init_matrix(&A, 1, 1, values);

  // ACT: Calculate algebraic complement for 1x1 matrix
  int code = s21_calc_complements(&A, &B);

  // ASSERT: For 1x1 matrix, complement is always 1
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(B.rows, 1);
  ck_assert_int_eq(B.columns, 1);
  ck_assert_double_eq_tol(B.matrix[0][0], 1.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_calc_complements_not_square) {
  // ARRANGE: Create a non-square matrix (2x3)
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  s21_create_matrix(2, 3, &A);

  // ACT: Attempt to calculate complements for non-square matrix
  int code = s21_calc_complements(&A, &B);

  // ASSERT: Should return calculation error (matrix must be square)
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  // B was not created, no need to remove
}
END_TEST

START_TEST(test_calc_complements_null_pointer) {
  // ARRANGE: Create a valid matrix for comparison
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT & ASSERT: Test NULL pointer scenarios
  int code = s21_calc_complements(NULL, &B);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_identity) {
  // ARRANGE: Create a 2x2 identity matrix
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 0.0, 0.0, 1.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Calculate complements of identity matrix
  int code = s21_calc_complements(&A, &B);

  // ASSERT: Complements of identity matrix is also identity
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][1], 1.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *calc_complements_suite(void) {
  Suite *s = suite_create("calc_complements");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_calc_complements_2x2);
  tcase_add_test(tc, test_calc_complements_3x3);
  tcase_add_test(tc, test_calc_complements_1x1);
  tcase_add_test(tc, test_calc_complements_not_square);
  tcase_add_test(tc, test_calc_complements_null_pointer);
  tcase_add_test(tc, test_calc_complements_identity);

  suite_add_tcase(s, tc);
  return s;
}
