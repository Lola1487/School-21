#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Результат выполнения операций */
#define OK 0
#define ERROR 1
#define INCORRECT_MATRIX 1  ///< NULL или неверные размеры
#define CALC_ERROR 2  ///< Несовпадение размеров, деление на 0 и т.д.

/* Результат сравнения */
#define SUCCESS 1
#define FAILURE 0

typedef int operation_code_t;

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} s21_matrix;

int s21_create_matrix(int rows, int columns, s21_matrix *result);
void s21_remove_matrix(s21_matrix *A);
int s21_eq_matrix(const s21_matrix *A, const s21_matrix *B);
int s21_sum_matrix(const s21_matrix *A, const s21_matrix *B,
                   s21_matrix *result);
int s21_sub_matrix(const s21_matrix *A, const s21_matrix *B,
                   s21_matrix *result);
int s21_mult_number(const s21_matrix *A, double number, s21_matrix *result);
int s21_mult_matrix(const s21_matrix *A, const s21_matrix *B,
                    s21_matrix *result);
int s21_transpose(const s21_matrix *A, s21_matrix *result);
int s21_determinant(const s21_matrix *A, double *result);
int s21_calc_complements(const s21_matrix *A, s21_matrix *result);
int s21_inverse_matrix(const s21_matrix *A, s21_matrix *result);

#endif  // S21_MATRIX_H
