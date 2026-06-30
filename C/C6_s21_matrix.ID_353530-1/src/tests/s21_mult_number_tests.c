#include "s21_test_runner.h"

START_TEST(test_mult_number_normal) {
  // ARRANGE: Create a 2x2 matrix with test values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Multiply matrix by scalar 2.0
  int code = s21_mult_number(&A, 2.0, &B);

  // ASSERT: Verify each element is doubled
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][0], 2.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[0][1], 4.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][0], 6.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][1], 8.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_zero) {
  // ARRANGE: Create a 2x2 matrix with test values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Multiply matrix by zero
  int code = s21_mult_number(&A, 0.0, &B);

  // ASSERT: All elements should become zero
  ck_assert_int_eq(code, OK);
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      ck_assert_double_eq_tol(B.matrix[i][j], 0.0, 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_negative) {
  // ARRANGE: Create a 2x2 matrix with test values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Multiply matrix by negative scalar (-1.0)
  int code = s21_mult_number(&A, -1.0, &B);

  // ASSERT: All elements should change sign
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][0], -1.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][1], -4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_fraction) {
  // ARRANGE: Create a 2x2 matrix with even values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {2.0, 4.0, 6.0, 8.0};
  init_matrix(&A, 2, 2, values);

  // ACT: Multiply matrix by fractional scalar (0.5)
  int code = s21_mult_number(&A, 0.5, &B);

  // ASSERT: Verify elements are halved
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[1][1], 4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_1x1) {
  // ARRANGE: Create a 1x1 matrix
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {5.0};
  init_matrix(&A, 1, 1, values);

  // ACT: Multiply 1x1 matrix by scalar
  int code = s21_mult_number(&A, 3.0, &B);

  // ASSERT: Verify scalar multiplication result
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][0], 15.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_3x3) {
  // ARRANGE: Create a 3x3 matrix with test values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 3, 3, values);

  // ACT: Multiply 3x3 matrix by scalar 2.0
  int code = s21_mult_number(&A, 2.0, &B);

  // ASSERT: Verify specific elements
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(B.matrix[0][0], 2.0, 1e-6);
  ck_assert_double_eq_tol(B.matrix[2][2], 18.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_null_pointer) {
  // ARRANGE: Create a valid matrix for comparison
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT & ASSERT: Test NULL pointer scenarios
  int code = s21_mult_number(NULL, 2.0, &B);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  code = s21_mult_number(&A, 2.0, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_number_large) {
  // ARRANGE: Create a 10x10 matrix filled with ones
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  s21_create_matrix(10, 10, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 1.0;
    }
  }

  // ACT: Multiply large matrix by scalar 5.0
  int code = s21_mult_number(&A, 5.0, &B);

  // ASSERT: All elements should become 5.0
  ck_assert_int_eq(code, OK);
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      ck_assert_double_eq_tol(B.matrix[i][j], 5.0, 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *mult_number_suite(void) {
  Suite *s = suite_create("mult_number");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_mult_number_normal);
  tcase_add_test(tc, test_mult_number_zero);
  tcase_add_test(tc, test_mult_number_negative);
  tcase_add_test(tc, test_mult_number_fraction);
  tcase_add_test(tc, test_mult_number_1x1);
  tcase_add_test(tc, test_mult_number_3x3);
  tcase_add_test(tc, test_mult_number_null_pointer);
  tcase_add_test(tc, test_mult_number_large);

  suite_add_tcase(s, tc);
  return s;
}
