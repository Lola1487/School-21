#include "s21_test_runner.h"

START_TEST(test_sub_matrix_normal) {
  // ARRANGE: Create two 2x2 matrices for subtraction (A - B)
  s21_matrix A, B, C;
  double values_a[] = {5.0, 6.0, 7.0, 8.0};
  double values_b[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 2, 2, values_b);

  // ACT: Perform matrix subtraction
  int code = s21_sub_matrix(&A, &B, &C);

  // ASSERT: Verify result is [4, 4; 4, 4]
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], 4.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[0][1], 4.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][0], 4.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][1], 4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_3x3) {
  // ARRANGE: Create two 3x3 matrices with complementary values
  s21_matrix A, B, C;
  double values_a[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
  double values_b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 3, 3, values_a);
  init_matrix(&B, 3, 3, values_b);

  // ACT: Perform matrix subtraction
  int code = s21_sub_matrix(&A, &B, &C);

  // ASSERT: Verify specific elements of the result
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], 8.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][1], 0.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[2][2], -8.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_different_size) {
  // ARRANGE: Create matrices with incompatible dimensions (2x2 and 3x3)
  s21_matrix A, B, C;
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 3, 3, values_b);

  // ACT: Attempt subtraction with mismatched dimensions
  int code = s21_sub_matrix(&A, &B, &C);

  // ASSERT: Should return calculation error
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_null_pointer) {
  // ARRANGE: Create valid matrices for comparison
  s21_matrix A, B, C;
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);
  init_matrix(&B, 2, 2, values);

  // ACT & ASSERT: Test each NULL pointer scenario
  int code = s21_sub_matrix(NULL, &B, &C);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_sub_matrix(&A, NULL, &C);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_1x1) {
  // ARRANGE: Create two 1x1 matrices
  s21_matrix A, B, C;
  double values_a[] = {10.0};
  double values_b[] = {3.0};
  init_matrix(&A, 1, 1, values_a);
  init_matrix(&B, 1, 1, values_b);

  // ACT: Subtract 1x1 matrices (scalar subtraction)
  int code = s21_sub_matrix(&A, &B, &C);

  // ASSERT: Verify scalar difference
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], 7.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_negative_result) {
  // ARRANGE: Create matrices where A < B (result will be negative)
  s21_matrix A, B, C;
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {5.0, 6.0, 7.0, 8.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 2, 2, values_b);

  // ACT: Perform subtraction where result has negative values
  int code = s21_sub_matrix(&A, &B, &C);

  // ASSERT: Verify negative results
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(C.matrix[0][0], -4.0, 1e-6);
  ck_assert_double_eq_tol(C.matrix[1][1], -4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_same_matrix) {
  // ARRANGE: Create two identical matrices
  s21_matrix A, B, C;
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);
  init_matrix(&B, 2, 2, values);

  // ACT: Subtract matrix from itself
  int code = s21_sub_matrix(&A, &B, &C);

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

Suite *sub_matrix_suite(void) {
  Suite *s = suite_create("sub_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_sub_matrix_normal);
  tcase_add_test(tc, test_sub_matrix_3x3);
  tcase_add_test(tc, test_sub_matrix_different_size);
  tcase_add_test(tc, test_sub_matrix_null_pointer);
  tcase_add_test(tc, test_sub_matrix_1x1);
  tcase_add_test(tc, test_sub_matrix_negative_result);
  tcase_add_test(tc, test_sub_matrix_same_matrix);

  suite_add_tcase(s, tc);
  return s;
}
