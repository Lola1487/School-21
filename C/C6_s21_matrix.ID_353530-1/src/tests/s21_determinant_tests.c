#include "s21_test_runner.h"

START_TEST(test_determinant_1x1) {
  // ARRANGE: Create a 1x1 matrix
  s21_matrix A;
  double values[] = {5.0};
  init_matrix(&A, 1, 1, values);

  // ACT: Calculate determinant
  double det;
  int code = s21_determinant(&A, &det);

  // ASSERT: Determinant of 1x1 matrix is the element itself
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(det, 5.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2) {
  // ARRANGE: Create a 2x2 matrix
  s21_matrix A;
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Calculate determinant
  double det;
  int code = s21_determinant(&A, &det);

  // ASSERT: Verify using formula ad - bc = 1*4 - 2*3 = -2
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(det, -2.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3) {
  // ARRANGE: Create a 3x3 singular matrix (rows are linearly dependent)
  s21_matrix A;
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 3, 3, values);

  // ACT: Calculate determinant
  double det;
  int code = s21_determinant(&A, &det);

  // ASSERT: Determinant should be zero for singular matrix
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(det, 0.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_not_square) {
  // ARRANGE: Create a non-square matrix (2x3)
  s21_matrix A;
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  init_matrix(&A, 2, 3, values);

  // ACT: Attempt to calculate determinant of non-square matrix
  double det;
  int code = s21_determinant(&A, &det);

  // ASSERT: Should return calculation error (determinant defined only for
  // square matrices)
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_null_pointer) {
  // ACT & ASSERT: Test with NULL matrix pointer
  double det;
  int code = s21_determinant(NULL, &det);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  // ARRANGE: Create a valid matrix for second test
  s21_matrix A;
  double values[] = {1.0};
  init_matrix(&A, 1, 1, values);

  // ACT & ASSERT: Test with NULL result pointer
  code = s21_determinant(&A, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

Suite *determinant_suite(void) {
  Suite *s = suite_create("determinant");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_determinant_1x1);
  tcase_add_test(tc, test_determinant_2x2);
  tcase_add_test(tc, test_determinant_3x3);
  tcase_add_test(tc, test_determinant_not_square);
  tcase_add_test(tc, test_determinant_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}
