#include "s21_test_runner.h"

START_TEST(test_sum_matrix_normal) {
  // ARRANGE: Create two 2x2 matrices with test values
  s21_matrix A, B, C;
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {5.0, 6.0, 7.0, 8.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 2, 2, values_b);

  // ACT: Perform matrix addition
  int code = s21_sum_matrix(&A, &B, &C);

  // ASSERT: Verify result dimensions and element-wise sum
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(C.rows, 2);
  ck_assert_int_eq(C.columns, 2);
  ck_assert_double_eq_tol(C.matrix[0][0], 6.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[0][1], 8.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][0], 10.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][1], 12.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_matrix_3x3) {
  // ARRANGE: Create two 3x3 matrices with complementary values
  s21_matrix A, B, C;
  double values_a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  double values_b[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
  init_matrix(&A, 3, 3, values_a);
  init_matrix(&B, 3, 3, values_b);

  // ACT: Perform matrix addition
  int code = s21_sum_matrix(&A, &B, &C);

  // ASSERT: All elements should sum to 10.0
  ck_assert_int_eq(code, OK);
  for (int i = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_double_eq_tol(C.matrix[i][j], 10.0, 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_matrix_different_size) {
  // ARRANGE: Create matrices with incompatible dimensions (2x2 and 3x3)
  s21_matrix A, B, C;
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 3, 3, values_b);

  // ACT: Attempt addition with mismatched dimensions
  int code = s21_sum_matrix(&A, &B, &C);

  // ASSERT: Should return calculation error
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_null_pointer) {
  // ARRANGE: Create valid matrices for comparison
  s21_matrix A, B, C;
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);
  init_matrix(&B, 2, 2, values);

  // ACT & ASSERT: Test each NULL pointer scenario
  int code = s21_sum_matrix(NULL, &B, &C);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_sum_matrix(&A, NULL, &C);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_1x1) {
  // ARRANGE: Create two 1x1 matrices
  s21_matrix A, B, C;
  double values_a[] = {5.0};
  double values_b[] = {3.0};
  init_matrix(&A, 1, 1, values_a);
  init_matrix(&B, 1, 1, values_b);

  // ACT: Add 1x1 matrices (scalar addition)
  int code = s21_sum_matrix(&A, &B, &C);

  // ASSERT: Verify scalar sum
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], 8.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_matrix_negative) {
  // ARRANGE: Create matrices with negative and positive values
  s21_matrix A, B, C;
  double values_a[] = {-1.0, -2.0, -3.0, -4.0};
  double values_b[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 2, 2, values_b);

  // ACT: Add matrices with opposite signs
  int code = s21_sum_matrix(&A, &B, &C);

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

START_TEST(test_sum_matrix_zeros) {
  // ARRANGE: Create two zero matrices
  s21_matrix A, B, C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // ACT: Add zero matrices
  int code = s21_sum_matrix(&A, &B, &C);

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

Suite *sum_matrix_suite(void) {
  Suite *s = suite_create("sum_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_sum_matrix_normal);
  tcase_add_test(tc, test_sum_matrix_3x3);
  tcase_add_test(tc, test_sum_matrix_different_size);
  tcase_add_test(tc, test_sum_matrix_null_pointer);
  tcase_add_test(tc, test_sum_matrix_1x1);
  tcase_add_test(tc, test_sum_matrix_negative);
  tcase_add_test(tc, test_sum_matrix_zeros);

  suite_add_tcase(s, tc);
  return s;
}
