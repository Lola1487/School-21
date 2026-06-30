/* =^..^= */
#include "s21_matrix.h"

static const double S21_EPSILON = 1e-6;

/* Processing statuses */
typedef enum {
  PROCESSING_DO = 0,
  PROCESSING_DONE = 1,
} status_t;

typedef enum {
  SUMMARY_MATRIX = 1,
  SUBSTRACTION_MATRIX = -1
} matrix_operation_t;

static int is_correct_matrix(const s21_matrix *matrix);
static int is_same_size(const s21_matrix *A, const s21_matrix *B);
static inline int compare_double(double a, double b);
static int sum_or_sub_matrix(const s21_matrix *A, const s21_matrix *B,
                             s21_matrix *result, matrix_operation_t operation);
static int get_minor(const s21_matrix *A, int row_to_skip, int col_to_skip,
                     s21_matrix *minor);
static int is_square_matrix(const s21_matrix *A);
static int calc_determinant_recursive(const s21_matrix *A, double *result);

int s21_create_matrix(int rows, int columns, s21_matrix *result) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  /* Safe initialization */
  if (result != NULL) {
    result->matrix = NULL;
    result->rows = 0;
    result->columns = 0;
  }

  /* Step 1: Validate input pointer */
  if (result == NULL) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  /* Step 2: Validate input parameters */
  if (rows <= 0 || columns <= 0) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  if (process_state == PROCESSING_DO) {
    int number_of_pointers = rows;
    size_t size_of_one_pointer = sizeof(double *);
    size_t total_memory = number_of_pointers * size_of_one_pointer;
    double **pointers_array = malloc(total_memory);
    result->matrix = pointers_array;

    if (result->matrix == NULL) {
      process_state = PROCESSING_DONE;
      operation_code = ERROR;
    }
  }

  /* Step 4: Allocate memory for each row */
  for (int i = 0; process_state == PROCESSING_DO && i < rows; i++) {
    int number_of_elements = columns;
    size_t size_of_one_element = sizeof(double);
    size_t total_memory = number_of_elements * size_of_one_element;
    double *array = malloc(total_memory);
    result->matrix[i] = array;

    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
        result->matrix[j] = NULL;
      }
      free(result->matrix);
      result->matrix = NULL;
      result->rows = 0;
      result->columns = 0;
      process_state = PROCESSING_DONE;
      operation_code = ERROR;
      break;
    }
  }

  /* Step 5: Store matrix dimensions */
  if (process_state == PROCESSING_DO) {
    result->rows = rows;
    result->columns = columns;

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0.0;
      }
    }
  }
  return operation_code;
}

void s21_remove_matrix(s21_matrix *A) {
  if (A == NULL || A->matrix == NULL) {
    return;
  }
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] != NULL) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(const s21_matrix *A, const s21_matrix *B) {
  int result = SUCCESS;
  if (!is_correct_matrix(A) || !is_correct_matrix(B)) {
    result = FAILURE;
  }
  if (result == SUCCESS && !is_same_size(A, B)) {
    result = FAILURE;
  }
  if (result == SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (!compare_double(A->matrix[i][j], B->matrix[i][j])) {
          result = FAILURE;
          break;
        }
      }
    }
  }
  return result;
}

int s21_sum_matrix(const s21_matrix *A, const s21_matrix *B,
                   s21_matrix *result) {
  return sum_or_sub_matrix(A, B, result, SUMMARY_MATRIX);
}

int s21_sub_matrix(const s21_matrix *A, const s21_matrix *B,
                   s21_matrix *result) {
  return sum_or_sub_matrix(A, B, result, SUBSTRACTION_MATRIX);
}

int s21_mult_number(const s21_matrix *A, double number, s21_matrix *result) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  if (!is_correct_matrix(A) || result == NULL) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_create_matrix(A->rows, A->columns, result);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return operation_code;
}

int s21_mult_matrix(const s21_matrix *A, const s21_matrix *B,
                    s21_matrix *result) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  if (!is_correct_matrix(A) || !is_correct_matrix(B) || result == NULL) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  if (process_state == PROCESSING_DO && A->columns != B->rows) {
    process_state = PROCESSING_DONE;
    operation_code = CALC_ERROR;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_create_matrix(A->rows, B->columns, result);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        double dot_product = 0.0;
        for (int k = 0; k < A->columns; k++) {
          dot_product += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = dot_product;
      }
    }
  }
  return operation_code;
}

int s21_transpose(const s21_matrix *A, s21_matrix *result) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  if (!is_correct_matrix(A) || result == NULL) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_create_matrix(A->columns, A->rows, result);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return operation_code;
}

int s21_determinant(const s21_matrix *A, double *result) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  if (!is_correct_matrix(A) || result == NULL) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  if (process_state == PROCESSING_DO && !is_square_matrix(A)) {
    process_state = PROCESSING_DONE;
    operation_code = CALC_ERROR;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = calc_determinant_recursive(A, result);
  }
  return operation_code;
}

int s21_calc_complements(const s21_matrix *A, s21_matrix *result) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  if (!is_correct_matrix(A) || result == NULL) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  if (process_state == PROCESSING_DO && !is_square_matrix(A)) {
    process_state = PROCESSING_DONE;
    operation_code = CALC_ERROR;
  }

  if (process_state == PROCESSING_DO && A->rows == 1 && A->columns == 1) {
    operation_code = s21_create_matrix(1, 1, result);
    if (operation_code == OK) {
      result->matrix[0][0] = 1.0;
    }
    process_state = PROCESSING_DONE;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_create_matrix(A->rows, A->columns, result);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (process_state != PROCESSING_DO) break;
        s21_matrix minor = {NULL, 0, 0};
        double minor_det = 0.0;
        double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;

        operation_code = get_minor(A, i, j, &minor);
        if (operation_code == OK) {
          operation_code = calc_determinant_recursive(&minor, &minor_det);
        }
        if (operation_code == OK) {
          result->matrix[i][j] = sign * minor_det;
        } else {
          process_state = PROCESSING_DONE;
        }
        s21_remove_matrix(&minor);
      }
    }
  }

  if (operation_code != OK && result != NULL && result->matrix != NULL) {
    s21_remove_matrix(result);
  }
  return operation_code;
}

int s21_inverse_matrix(const s21_matrix *A, s21_matrix *result) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;
  double det = 0.0;
  s21_matrix cofactors = {NULL, 0, 0};
  s21_matrix transposed = {NULL, 0, 0};

  if (!is_correct_matrix(A) || result == NULL) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  if (process_state == PROCESSING_DO && !is_square_matrix(A)) {
    process_state = PROCESSING_DONE;
    operation_code = CALC_ERROR;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = calc_determinant_recursive(A, &det);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO && compare_double(det, 0.0)) {
    process_state = PROCESSING_DONE;
    operation_code = CALC_ERROR;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_calc_complements(A, &cofactors);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_transpose(&cofactors, &transposed);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_mult_number(&transposed, 1.0 / det, result);
  }

  s21_remove_matrix(&cofactors);
  s21_remove_matrix(&transposed);
  return operation_code;
}

static int is_correct_matrix(const s21_matrix *matrix) {
  return (matrix != NULL && matrix->matrix != NULL && matrix->columns > 0 &&
          matrix->rows > 0)
             ? SUCCESS
             : FAILURE;
}

static int is_same_size(const s21_matrix *A, const s21_matrix *B) {
  return (A->rows == B->rows && A->columns == B->columns) ? SUCCESS : FAILURE;
}

static inline int compare_double(double a, double b) {
  return fabs(a - b) < S21_EPSILON;
}

static int sum_or_sub_matrix(const s21_matrix *A, const s21_matrix *B,
                             s21_matrix *result, matrix_operation_t operation) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  if (!is_correct_matrix(A) || !is_correct_matrix(B) || result == NULL) {
    process_state = PROCESSING_DONE;
    operation_code = INCORRECT_MATRIX;
  }

  if (process_state == PROCESSING_DO && !is_same_size(A, B)) {
    process_state = PROCESSING_DONE;
    operation_code = CALC_ERROR;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_create_matrix(A->rows, A->columns, result);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + operation * B->matrix[i][j];
      }
    }
  }
  return operation_code;
}

static int get_minor(const s21_matrix *A, int row_to_skip, int col_to_skip,
                     s21_matrix *minor) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  if (A->rows < 2 || A->columns < 2) {
    process_state = PROCESSING_DONE;
    operation_code = CALC_ERROR;
  }

  if (process_state == PROCESSING_DO) {
    operation_code = s21_create_matrix(A->rows - 1, A->columns - 1, minor);
    if (operation_code != OK) {
      process_state = PROCESSING_DONE;
    }
  }

  if (process_state == PROCESSING_DO) {
    int mi = 0;
    for (int i = 0; i < A->rows; i++) {
      if (i == row_to_skip) continue;
      int mj = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j == col_to_skip) continue;
        minor->matrix[mi][mj] = A->matrix[i][j];
        mj++;
      }
      mi++;
    }
  }
  return operation_code;
}

static int is_square_matrix(const s21_matrix *A) {
  return (A->rows == A->columns) ? SUCCESS : FAILURE;
}

static int calc_determinant_recursive(const s21_matrix *A, double *result) {
  status_t process_state = PROCESSING_DO;
  operation_code_t operation_code = OK;

  if (A->rows == 1) {
    *result = A->matrix[0][0];
    process_state = PROCESSING_DONE;
  }

  if (process_state == PROCESSING_DO && A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    process_state = PROCESSING_DONE;
  }

  if (process_state == PROCESSING_DO) {
    *result = 0.0;
    for (int j = 0; process_state == PROCESSING_DO && j < A->columns; j++) {
      s21_matrix minor = {NULL, 0, 0};
      double minor_det = 0.0;
      double cofactor_sign = (j % 2 == 0) ? 1.0 : -1.0;

      operation_code = get_minor(A, 0, j, &minor);
      if (operation_code == OK) {
        operation_code = calc_determinant_recursive(&minor, &minor_det);
      }

      if (operation_code == OK) {
        *result += cofactor_sign * A->matrix[0][j] * minor_det;
      } else {
        process_state = PROCESSING_DONE;
      }
      s21_remove_matrix(&minor);
    }
  }
  return operation_code;
}
