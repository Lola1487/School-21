#include "s21_test_runner.h"

START_TEST(test_transpose_2x2) {
  // ARRANGE: Create a 2x2 matrix with test values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Transpose the matrix
  int code = s21_transpose(&A, &B);

  // ASSERT: Verify transposed matrix dimensions and values
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(B.rows, 2);
  ck_assert_int_eq(B.columns, 2);
  ck_assert_double_eq_tol(B.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[0][1], 3.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][0], 2.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][1], 4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_3x3) {
  // ARRANGE: Create a 3x3 matrix with test values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 3, 3, values);

  // ACT: Transpose the matrix
  int code = s21_transpose(&A, &B);

  // ASSERT: Verify specific transposed elements
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][2], 7.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[2][0], 3.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_rectangular) {
  // ARRANGE: Create a 2x3 rectangular matrix
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  // ACT: Transpose rectangular matrix
  int code = s21_transpose(&A, &B);

  // ASSERT: Verify dimensions change (2x3 -> 3x2) and values
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(B.rows, 3);
  ck_assert_int_eq(B.columns, 2);
  ck_assert_double_eq_tol(B.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[2][1], 6.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_1x1) {
  // ARRANGE: Create a 1x1 matrix
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {5.0};
  init_matrix(&A, 1, 1, values);

  // ACT: Transpose the 1x1 matrix
  int code = s21_transpose(&A, &B);

  // ASSERT: Value remains unchanged
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][0], 5.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_row_vector) {
  // ARRANGE: Create a 1x4 row vector
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  s21_create_matrix(1, 4, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = 4.0;

  // ACT: Transpose row vector to column vector
  int code = s21_transpose(&A, &B);

  // ASSERT: Verify dimensions (1x4 -> 4x1) and value
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(B.rows, 4);
  ck_assert_int_eq(B.columns, 1);
  ck_assert_double_eq_tol(B.matrix[3][0], 4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_column_vector) {
  // ARRANGE: Create a 4x1 column vector
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  s21_create_matrix(4, 1, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[1][0] = 2.0;
  A.matrix[2][0] = 3.0;
  A.matrix[3][0] = 4.0;

  // ACT: Transpose column vector to row vector
  int code = s21_transpose(&A, &B);

  // ASSERT: Verify dimensions (4x1 -> 1x4) and value
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(B.rows, 1);
  ck_assert_int_eq(B.columns, 4);
  ck_assert_double_eq_tol(B.matrix[0][3], 4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_null_pointer) {
  // ARRANGE: Create a valid matrix for comparison
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT & ASSERT: Test NULL pointer scenarios
  int code = s21_transpose(NULL, &B);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_transpose(&A, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transpose_double) {
  // ARRANGE: Create original matrix
  s21_matrix A, B, C;
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Transpose twice
  s21_transpose(&A, &B);
  s21_transpose(&B, &C);

  // ASSERT: Double transpose should return original matrix
  ck_assert_int_eq(s21_eq_matrix(&A, &C), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

Suite *transpose_suite(void) {
  Suite *s = suite_create("transpose");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_transpose_2x2);
  tcase_add_test(tc, test_transpose_3x3);
  tcase_add_test(tc, test_transpose_rectangular);
  tcase_add_test(tc, test_transpose_1x1);
  tcase_add_test(tc, test_transpose_row_vector);
  tcase_add_test(tc, test_transpose_column_vector);
  tcase_add_test(tc, test_transpose_null_pointer);
  tcase_add_test(tc, test_transpose_double);

  suite_add_tcase(s, tc);
  return s;
}
