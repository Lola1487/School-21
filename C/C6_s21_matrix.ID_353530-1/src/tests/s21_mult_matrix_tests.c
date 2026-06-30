#include "s21_test_runner.h"

START_TEST(test_mult_matrix_2x2) {
  // ARRANGE: Initialize two 2x2 matrices with test values
  s21_matrix A, B, C;
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {5.0, 6.0, 7.0, 8.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 2, 2, values_b);

  // ACT: Perform matrix multiplication
  int code = s21_mult_matrix(&A, &B, &C);

  // ASSERT: Verify result and clean up
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], 19.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[0][1], 22.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][0], 43.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][1], 50.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_matrix_3x3) {
  // ARRANGE: Initialize two 3x3 matrices with test values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0}, C = {NULL, 0, 0};
  double values_a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  double values_b[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
  init_matrix(&A, 3, 3, values_a);
  init_matrix(&B, 3, 3, values_b);

  // ACT: Perform matrix multiplication
  int code = s21_mult_matrix(&A, &B, &C);

  // ASSERT: Verify key elements of the result
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], 30.0, 1e-6);  // 1*9+2*6+3*3
  ck_assert_double_eq_tol(C.matrix[1][1], 69.0, 1e-6);  // 4*8+5*5+6*2
  ck_assert_double_eq_tol(C.matrix[2][2], 90.0, 1e-6);  // 7*7+8*4+9*1

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_matrix_identity) {
  // ARRANGE: Create a matrix and an identity matrix
  s21_matrix A, B, C;
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {1.0, 0.0, 0.0, 1.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 2, 2, values_b);

  // ACT: Multiply matrix A by identity matrix
  int code = s21_mult_matrix(&A, &B, &C);

  // ASSERT: Result should equal original matrix A
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[0][1], 2.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][0], 3.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][1], 4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_matrix_dimension_mismatch) {
  // ARRANGE: Create matrices with incompatible dimensions (2x2 and 3x3)
  s21_matrix A, B, C;
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 3, 3, values_b);

  // ACT: Attempt multiplication with mismatched dimensions
  int code = s21_mult_matrix(&A, &B, &C);

  // ASSERT: Should return calculation error
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_rectangular) {
  // ARRANGE: Create rectangular matrices (2x3 and 3x2)
  s21_matrix A, B, C;

  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  s21_create_matrix(3, 2, &B);
  B.matrix[0][0] = 7.0;
  B.matrix[0][1] = 8.0;
  B.matrix[1][0] = 9.0;
  B.matrix[1][1] = 10.0;
  B.matrix[2][0] = 11.0;
  B.matrix[2][1] = 12.0;

  // ACT: Multiply rectangular matrices
  int code = s21_mult_matrix(&A, &B, &C);

  // ASSERT: Verify result dimensions and values
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(C.rows, 2);
  ck_assert_int_eq(C.columns, 2);
  ck_assert_double_eq_tol(C.matrix[0][0], 58.0, 1e-6);  // 1*7 + 2*9 + 3*11
  ck_assert_double_eq_tol(C.matrix[0][1], 64.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][0], 139.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][1], 154.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_matrix_1x1) {
  // ARRANGE: Create two 1x1 matrices
  s21_matrix A, B, C;
  double values_a[] = {5.0};
  double values_b[] = {3.0};
  init_matrix(&A, 1, 1, values_a);
  init_matrix(&B, 1, 1, values_b);

  // ACT: Multiply 1x1 matrices
  int code = s21_mult_matrix(&A, &B, &C);

  // ASSERT: Verify scalar multiplication result
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], 15.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_matrix_null_pointer) {
  // ARRANGE: Create valid matrices for comparison
  s21_matrix A, B, C;
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);
  init_matrix(&B, 2, 2, values);

  // ACT & ASSERT: Test each NULL pointer scenario
  int code = s21_mult_matrix(NULL, &B, &C);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_mult_matrix(&A, NULL, &C);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_mult_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_zeros) {
  // ARRANGE: Create two zero matrices
  s21_matrix A, B, C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // ACT: Multiply zero matrices
  int code = s21_mult_matrix(&A, &B, &C);

  // ASSERT: Result should be zero matrix
  ck_assert_int_eq(code, OK);
  for (int i = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_double_eq_tol(C.matrix[i][j], 0.0, 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

Suite *mult_matrix_suite(void) {
  Suite *s = suite_create("mult_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_mult_matrix_2x2);
  tcase_add_test(tc, test_mult_matrix_3x3);
  tcase_add_test(tc, test_mult_matrix_identity);
  tcase_add_test(tc, test_mult_matrix_dimension_mismatch);
  tcase_add_test(tc, test_mult_matrix_rectangular);
  tcase_add_test(tc, test_mult_matrix_1x1);
  tcase_add_test(tc, test_mult_matrix_null_pointer);
  tcase_add_test(tc, test_mult_matrix_zeros);

  suite_add_tcase(s, tc);
  return s;
}
