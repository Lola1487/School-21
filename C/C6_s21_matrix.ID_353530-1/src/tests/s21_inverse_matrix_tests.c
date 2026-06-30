#include "s21_test_runner.h"

START_TEST(test_inverse_2x2) {
  // ARRANGE: Create a 2x2 invertible matrix
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0}, C = {NULL, 0, 0};
  double values[] = {4.0, 7.0, 2.0, 6.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Calculate the inverse matrix
  int code = s21_inverse_matrix(&A, &B);

  // ASSERT: Verify that A * A^(-1) = Identity matrix
  ck_assert_int_eq(code, OK);

  code = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(code, OK);

  ck_assert_double_eq_tol(C.matrix[0][0], 1.0, 1e-5);
  ck_assert_double_eq_tol(C.matrix[0][1], 0.0, 1e-5);
  ck_assert_double_eq_tol(C.matrix[1][0], 0.0, 1e-5);
  ck_assert_double_eq_tol(C.matrix[1][1], 1.0, 1e-5);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_3x3) {
  // ARRANGE: Create a 3x3 invertible matrix
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0}, C = {NULL, 0, 0};
  double values[] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};
  init_matrix(&A, 3, 3, values);

  // ACT: Calculate the inverse matrix
  int code = s21_inverse_matrix(&A, &B);

  // ASSERT: Verify that A * A^(-1) = Identity matrix
  ck_assert_int_eq(code, OK);

  code = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(code, OK);

  ck_assert_double_eq_tol(C.matrix[0][0], 1.0, 1e-5);
  ck_assert_double_eq_tol(C.matrix[1][1], 1.0, 1e-5);
  ck_assert_double_eq_tol(C.matrix[2][2], 1.0, 1e-5);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_singular) {
  // ARRANGE: Create a singular matrix with zero determinant
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 3, 3, values);

  // ACT: Attempt to calculate inverse of singular matrix
  int code = s21_inverse_matrix(&A, &B);

  // ASSERT: Should return calculation error (matrix is not invertible)
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_not_square) {
  // ARRANGE: Create a non-square matrix (2x3)
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  init_matrix(&A, 2, 3, values);  // 2 rows × 3 columns = 6 elements

  // ACT: Attempt to calculate inverse of non-square matrix
  int code = s21_inverse_matrix(&A, &B);

  // ASSERT: Should return calculation error (only square matrices have
  // inverses)
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_1x1) {
  // ARRANGE: Create a 1x1 matrix
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {5.0};
  init_matrix(&A, 1, 1, values);

  // ACT: Calculate inverse of 1x1 matrix
  int code = s21_inverse_matrix(&A, &B);

  // ASSERT: Inverse of [5] is [0.2] (1/5)
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][0], 0.2, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_inverse_null_pointer) {
  // ARRANGE: Create a valid matrix for comparison
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT & ASSERT: Test NULL pointer scenarios
  int code = s21_inverse_matrix(NULL, &B);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

Suite *inverse_matrix_suite(void) {
  Suite *s = suite_create("inverse_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_inverse_2x2);
  tcase_add_test(tc, test_inverse_3x3);
  tcase_add_test(tc, test_inverse_singular);
  tcase_add_test(tc, test_inverse_not_square);
  tcase_add_test(tc, test_inverse_1x1);
  tcase_add_test(tc, test_inverse_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}
