#ifndef S21_TEST_RUNNER_H
#define S21_TEST_RUNNER_H

#include <check.h>

#include "../s21_matrix.h"

// Объявления всех suite-функций (определяются в соответствующих *_tests.c
// файлах)
Suite *create_matrix_suite(void);
Suite *remove_matrix_suite(void);
Suite *eq_matrix_suite(void);
Suite *sum_matrix_suite(void);
Suite *sub_matrix_suite(void);
Suite *mult_number_suite(void);
Suite *mult_matrix_suite(void);
Suite *transpose_suite(void);
Suite *determinant_suite(void);
Suite *calc_complements_suite(void);
Suite *inverse_matrix_suite(void);

// Вспомогательная функция для инициализации матрицы из массива
void init_matrix(s21_matrix *A, int rows, int columns, const double values[]);

#endif  // S21_TEST_RUNNER_H
