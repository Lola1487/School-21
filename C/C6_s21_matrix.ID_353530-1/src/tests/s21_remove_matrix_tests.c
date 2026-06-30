#include "s21_test_runner.h"

START_TEST(test_remove_matrix_normal) {
  // ARRANGE: Create and populate a 3x3 matrix
  s21_matrix A;
  s21_create_matrix(3, 3, &A);

  // Fill with some values
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i * A.columns + j;
    }
  }

  // ACT: Free the matrix memory
  s21_remove_matrix(&A);

  // ASSERT: Verify matrix is reset to zero/null state
  ck_assert_ptr_eq(A.matrix, NULL);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_1x1) {
  // ARRANGE: Create and populate a 1x1 matrix
  s21_matrix A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 42.0;

  // ACT: Free the matrix memory
  s21_remove_matrix(&A);

  // ASSERT: Verify matrix is reset to zero/null state
  ck_assert_ptr_eq(A.matrix, NULL);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_null_pointer) {
  // ARRANGE: No setup needed - testing with NULL pointer

  // ACT & ASSERT: Function should handle NULL pointer gracefully without
  // crashing
  s21_remove_matrix(NULL);
  // No assertions needed - test passes if no crash occurs
}
END_TEST

START_TEST(test_remove_matrix_already_freed) {
  // ARRANGE: Create a matrix and free it once
  s21_matrix A;
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);

  // ACT: Attempt to free already freed matrix
  s21_remove_matrix(&A);

  // ASSERT: Second remove should not crash and matrix should remain NULL
  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

START_TEST(test_remove_matrix_large) {
  // ARRANGE: Create a large 100x100 matrix and populate it
  s21_matrix A;
  s21_create_matrix(100, 100, &A);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (double)(i + j);
    }
  }

  // ACT: Free the large matrix memory
  s21_remove_matrix(&A);

  // ASSERT: Verify matrix is reset to zero/null state
  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

Suite *remove_matrix_suite(void) {
  Suite *s = suite_create("remove_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_remove_matrix_normal);
  tcase_add_test(tc, test_remove_matrix_1x1);
  tcase_add_test(tc, test_remove_matrix_null_pointer);
  tcase_add_test(tc, test_remove_matrix_already_freed);
  tcase_add_test(tc, test_remove_matrix_large);

  suite_add_tcase(s, tc);
  return s;
}
