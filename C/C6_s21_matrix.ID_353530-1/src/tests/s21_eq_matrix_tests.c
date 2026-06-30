#include "s21_test_runner.h"

START_TEST(test_eq_matrix_equal) {
  // ARRANGE: Create two identical 3x3 matrices
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 3, 3, values);
  init_matrix(&B, 3, 3, values);

  // ACT: Compare matrices for equality
  int result = s21_eq_matrix(&A, &B);

  // ASSERT: Matrices should be considered equal
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_not_equal) {
  // ARRANGE: Create two matrices with one different element
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values_a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  double values_b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0};
  init_matrix(&A, 3, 3, values_a);
  init_matrix(&B, 3, 3, values_b);

  // ACT: Compare matrices for equality
  int result = s21_eq_matrix(&A, &B);

  // ASSERT: Matrices should be considered different
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_different_size) {
  // ARRANGE: Create matrices with different dimensions (2x2 and 3x3)
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 3, 3, values_b);

  // ACT: Compare matrices with different sizes
  int result = s21_eq_matrix(&A, &B);

  // ASSERT: Matrices cannot be equal if dimensions differ
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_precision) {
  // ARRANGE: Create matrices with values within tolerance (difference < 1e-6)
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values_a[] = {1.0000001, 2.0, 3.0, 4.0};
  double values_b[] = {1.0000002, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 2, 2, values_b);

  // ACT: Compare matrices with tiny difference
  int result = s21_eq_matrix(&A, &B);

  // ASSERT: Difference is less than 1e-6, should be considered equal
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_precision_fail) {
  // ARRANGE: Create matrices with values exceeding tolerance (difference >
  // 1e-6)
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values_a[] = {1.0, 2.0, 3.0, 4.0};
  double values_b[] = {1.00001, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values_a);
  init_matrix(&B, 2, 2, values_b);

  // ACT: Compare matrices with noticeable difference
  int result = s21_eq_matrix(&A, &B);

  // ASSERT: Difference exceeds 1e-6, should not be equal
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_1x1_equal) {
  // ARRANGE: Create two identical 1x1 matrices
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {5.0};
  init_matrix(&A, 1, 1, values);
  init_matrix(&B, 1, 1, values);

  // ACT: Compare 1x1 matrices for equality
  int result = s21_eq_matrix(&A, &B);

  // ASSERT: Single-element matrices should be equal
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_null_pointer) {
  // ARRANGE: Create a valid matrix for comparison
  s21_matrix A;
  double values[] = {1.0, 2.0, 3.0, 4.0};
  init_matrix(&A, 2, 2, values);

  // ACT & ASSERT: Test NULL pointer scenarios (should return FAILURE)
  int result = s21_eq_matrix(NULL, &A);
  ck_assert_int_eq(result, FAILURE);

  result = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_matrix_negative_values) {
  // ARRANGE: Create two identical matrices with negative values
  s21_matrix A = {NULL, 0, 0}, B = {NULL, 0, 0};
  double values[] = {-1.0, -2.0, -3.0, -4.0};
  init_matrix(&A, 2, 2, values);
  init_matrix(&B, 2, 2, values);

  // ACT: Compare matrices with negative values
  int result = s21_eq_matrix(&A, &B);

  // ASSERT: Negative values should be compared correctly
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *eq_matrix_suite(void) {
  Suite *s = suite_create("eq_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_eq_matrix_equal);
  tcase_add_test(tc, test_eq_matrix_not_equal);
  tcase_add_test(tc, test_eq_matrix_different_size);
  tcase_add_test(tc, test_eq_matrix_precision);
  tcase_add_test(tc, test_eq_matrix_precision_fail);
  tcase_add_test(tc, test_eq_matrix_1x1_equal);
  tcase_add_test(tc, test_eq_matrix_null_pointer);
  tcase_add_test(tc, test_eq_matrix_negative_values);

  suite_add_tcase(s, tc);
  return s;
}
